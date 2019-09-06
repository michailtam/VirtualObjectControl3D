#include <GL\glew.h>			// IMPORTANT: glew.h must first be included
#include "renderwindow.h"
#include <QtWidgets\qdesktopwidget.h>
#include <QtGui\qmouseevent>
#include <QtGui\qwheelevent>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <QtGui\qpainter.h>
#include <QtWidgets\QMessageBox>
#include <thread>
#include <chrono>
#include "tools\mathlib.h"


const float CAMERA_SPEED = 0.01;

// Path of the shader files
const string SHADER_PATH = "./shader/";

GLfloat rotintervalCube = 0.0f;			// Rotation interval for the cube
GLfloat rotintervalPyramid = 0.0f;		// Rotation interval for the pyramid

// Macros
#define NUM_ARRAY_ELEMENTS(a) sizeof(a)/sizeof(*a)	// Size of an element


// Constructor
RenderWindow::RenderWindow(int screenWidth, int screenHeight, InformationWindow* informationWnindow, QWidget* parent)
{
	// Setup the user interface
	ui.setupUi(this);	

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	// Init the face data structs
	QRect* mFaceRect = 0;					
	PoseEulerAngle* mPoseEulerAngles = 0;	
	PoseQuaternion* mPoseQuaternion = 0;	
	HeadPosition* mHeadPosition = 0;	

	mInformationWnindow = informationWnindow;
}

// Destructor
RenderWindow::~RenderWindow()
{
	delete mRenderer;
}

// Initialization of the window content and properties
void RenderWindow::initializeGL()
{
	// Get the Intel RS Manager init status. If it's false, terminate the application
	if (!mIntelRSManager.getInitStatus()) {
		QMessageBox msg;
		msg.setText("There was a problem with the initialization of the Camera F200. "
			"Please check if the camera is connected. The programm will terminate.");
		msg.setIcon(QMessageBox::Critical);
		msg.exec();

		exit(0);	// Terminate program
	}

	// Set the checkbox state to true of the logging information on the information window
	mInformationWnindow->getUIRef().stopCameraLog->setChecked(true);
	mInformationWnindow->getUIRef().stopUserLog->setChecked(true);
	
	// Set the camera device information on the information window
	map<string, string> deviceInfo;
	mIntelRSManager.getCameraDeviceInfo(&deviceInfo);
	mInformationWnindow->getUIRef().deviceName->setText(QString::fromStdString(deviceInfo["Device Name"]));
	mInformationWnindow->getUIRef().deviceModel->setText(QString::fromStdString(deviceInfo["Device Model"]));
	mInformationWnindow->getUIRef().deviceSerial->setText(QString::fromStdString(deviceInfo["Device Serial"]));
	
	// Split the string of the device streams
	istringstream f(deviceInfo["Device Streams"]);
	string s;
	while (getline(f, s, '%')) {

		// Check which streams are supported of the cam and log them on the information window by setting
		// the check to the stream
		if (s.compare("STREAM TYPE DEPTH") == 0) {
			mInformationWnindow->getUIRef().deviceDepthCam->setChecked(true);
		}
		if (s.compare("STREAM TYPE COLOR") == 0) {
			mInformationWnindow->getUIRef().deviceColorCam->setChecked(true);
		}
		if (s.compare("STREAM TYPE IR") == 0) {
			mInformationWnindow->getUIRef().deviceLazerProjector->setChecked(true);
		}
	}

	// Determine which OpenGL extensions are supported. If it returns GLEW_OK
	// the initialization succeeded and we can use the available extensions 
	// as well as core OpenGL functionality.
	GLenum status = glewInit();
	if (status != GLEW_OK) {
		cout << "Error: " << glewGetErrorString(status) << endl;

		// We have to write exit(1) cause exit(0) indicates successful
		// program termination. Cause we want to keep our code portable 
		// for future, we have to use exit(0) cause exit(1) is not portable
		exit(0);
	}

	// Print the GLEW version
	cout << "OpenGL initialization started ...\n" << endl
		 << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;

	// Set window properties
	setWindowTitle("Virtual Object Control in 3D Environment");
	mAspectRatio = getWindowAspectRatio();

	// Set mouse tracking
	setMouseTracking(false);

	// Set the camera position
	vec3 cameraPosition(0.0f, 0.0f, 3.0f);
	vec3 viewDirection (0.0f, 0.0f, -3.0f);
	vec3 upVector(0.0f, 1.0f, 0.0f);
	mCamera.setCameraPosition(cameraPosition, viewDirection, upVector);
	mCamera.setCameraSpeed(CAMERA_SPEED);

	// Create the basic shader program
	mGLSLShaderManager.addShader(SHADER_PATH+"basic_shader.vs", GL_VERTEX_SHADER);
	mGLSLShaderManager.addShader(SHADER_PATH+"basic_shader.fs", GL_FRAGMENT_SHADER);
	mGLSLShaderManager.createProgram("standard");

	// Creates and inits the renderer who manages all drawing operations 
	mRenderer = new Renderer();
	mRenderer->init(mAspectRatio, &mCamera);
}

// Paint method
void RenderWindow::paintGL()
{
	// Clear the color and depth buffer
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	
	
	// Set background color to light grey
	glClearColor(0.7f, 0.7f, 0.8f, 1.0f);

	// What portion of the window we want to render to.
	// We want to render to the entire window
	glViewport(0, 0, width(), height());

	// Retrieve the shader program
	GLuint programID = mGLSLShaderManager.getProgramByName("standard");
	mGLSLShaderManager.useProgram("standard");	// Use the default shader program

	// Render all shapes of the scene and a light source
	mRenderer->renderCube(programID);		// Render a cube
	mRenderer->renderPyramid(programID);		// Render a pyramid
	mRenderer->renderTerrain(programID);		// Render a terrain
	mRenderer->renderLight(programID);		// Render a light source

	mGLSLShaderManager.detachProgram();		// Unuse shader program	

	captureIRSCameraData();					// Capture face data
}

// Gets the Intel RS data from the camera F200
void RenderWindow::captureIRSCameraData()
{
	static int count = 0;	// If count is 1, then start capturing

	// Save the old data captured from the cam (on the stack)
	static int prevFaceRectWidth = 0;
	static PoseEulerAngle prevPoseEulerAngles;

	// Capture the face data from the cam
	mIntelRSManager.captureDataFromCam(&mFaceRect, &mPoseEulerAngles);
	int faceRectWidth = mFaceRect.width();

	bool statusChanged = false;		// Log only if flag is set
	bool error = false;				// Set if error occurred

	// IMPORTANT: Don't capture the first frame cause the data of it is UNDEFINED
	if (count < 1)	count++;

	else {
		// Round the float values to 1 digit 
		mPoseEulerAngles.yaw = Mathlib::round_digits(mPoseEulerAngles.yaw, 1);
		prevPoseEulerAngles.yaw = Mathlib::round_digits(prevPoseEulerAngles.yaw, 1);
		mPoseEulerAngles.pitch = Mathlib::round_digits(mPoseEulerAngles.pitch, 1);
		prevPoseEulerAngles.pitch = Mathlib::round_digits(prevPoseEulerAngles.pitch, 1);

		// Calculate the difference between the old and the new pose euler angles
		float diffYaw = Mathlib::abs_difference(mPoseEulerAngles.yaw, prevPoseEulerAngles.yaw);
		float diffPitch = Mathlib::abs_difference(mPoseEulerAngles.pitch, prevPoseEulerAngles.pitch);

		// Set the yaw and pitch values for the camera movement. If the difference is greater than 0.1
		// only then execute the operation
		float newYaw = prevPoseEulerAngles.yaw;
		float newPitch = prevPoseEulerAngles.pitch;

		if (diffYaw > 0.1) {
			newYaw = mPoseEulerAngles.yaw;
			statusChanged = true;
		} 

		if (diffPitch > 0.1) {
			newPitch = mPoseEulerAngles.pitch;
			statusChanged = true;
		}

		// Move the camera and log the user and camera information on the ui only if status has changed
		if (statusChanged) {
			mCamera.move(faceRectWidth, newYaw, newPitch);	// Move the camera
			logDataOnUI(faceRectWidth, prevFaceRectWidth, mPoseEulerAngles, prevPoseEulerAngles);

			// Save current face width and the current pose euler angles
			prevFaceRectWidth = faceRectWidth;
			mPoseEulerAngles.yaw = newYaw;
			mPoseEulerAngles.pitch = newPitch;
		}
	}	

	//this_thread::sleep_for(std::chrono::milliseconds(2));		// Relax a few ms the CPU

	if (statusChanged && !error)
		update();	// Draw the new scene
	else
		captureIRSCameraData();	// Capture next data from camera
}

// Log the information of user and camera actions on the ui
void RenderWindow::logDataOnUI(int newWidth, int prevWidth, 
	PoseEulerAngle newPoseEulerAngles, PoseEulerAngle prevPoseEulerAngles) {

	// Flags for the logging actions.
	static bool isDepthForwardsLogged = false;
	static bool isDepthBackwardsLogged = false;
	static bool isYawLeftLogged = false;
	static bool isYawRightLogged = false;
	static bool isPitchUpLogged = false;
	static bool isPitchDownLogged = false;
	bool isYawDiffGreater = false;
	bool isPitchDiffGreater = false;

	int counts = 0;		// The last row of the list

		float yawDiff = Mathlib::abs_difference(newPoseEulerAngles.yaw, prevPoseEulerAngles.yaw);
		float pitchDiff = Mathlib::abs_difference(newPoseEulerAngles.pitch, prevPoseEulerAngles.pitch);

		if (yawDiff > pitchDiff) isYawDiffGreater = true;
		else if (pitchDiff > yawDiff) isPitchDiffGreater = true;
		else isYawDiffGreater = true;

		bool logCameraActions = false;
		bool logUserActions = false;

		// Log only the camera actions if the checkbox is checked 
		if (mInformationWnindow->getUIRef().stopCameraLog->isChecked())
			logCameraActions = true;

		// Log only the user actions if the checkbox is checked 
		if (mInformationWnindow->getUIRef().stopUserLog->isChecked())
			logUserActions = true;


		// THE CAMERA AND USER MOVEMENT LEFT OR RIGHT (YAW) 
		if (isYawDiffGreater) {
			float newYaw = Mathlib::round_digits(newPoseEulerAngles.yaw, 1);
			float prevYaw = Mathlib::round_digits(prevPoseEulerAngles.yaw, 1);

			if (newYaw > prevYaw) {
				// The camera and user move right
				if (!isYawRightLogged) {
					
					if (logCameraActions) {
						// Log yaw camera movement right
						mInformationWnindow->getUIRef().cameraActionsList->addItem("YAW RIGHT");
						counts = mInformationWnindow->getUIRef().cameraActionsList->count();
						mInformationWnindow->getUIRef().cameraActionsList->setCurrentRow(counts - 1);
					}
					
					if (logUserActions) {
						// Log yaw user movement right
						mInformationWnindow->getUIRef().userActionsList->addItem("TURN RIGHT");
						counts = mInformationWnindow->getUIRef().userActionsList->count();
						mInformationWnindow->getUIRef().userActionsList->setCurrentRow(counts - 1);
					}

					isYawLeftLogged = false;
					isYawRightLogged = true;
				}
			}
			// The camera and user move left
			else if (newYaw < prevYaw) {
				if (!isYawLeftLogged) {

					if (logCameraActions) {
						// Log depth camera movement left
						mInformationWnindow->getUIRef().cameraActionsList->addItem("YAW LEFT");
						counts = mInformationWnindow->getUIRef().cameraActionsList->count();
						mInformationWnindow->getUIRef().cameraActionsList->setCurrentRow(counts - 1);
					}

					if (logUserActions) {
						// Log depth user movement left
						mInformationWnindow->getUIRef().userActionsList->addItem("TURN LEFT");
						counts = mInformationWnindow->getUIRef().userActionsList->count();
						mInformationWnindow->getUIRef().userActionsList->setCurrentRow(counts - 1);
					}

					isYawLeftLogged = true;
					isYawRightLogged = false;
				}
			}
		}
		

		// THE CAMERA AND USER MOVEMENT UP OR DOWN (PITCH) 
		if (isPitchDiffGreater) {
			float newPitch = Mathlib::round_digits(newPoseEulerAngles.pitch, 1);
			float prevPitch = Mathlib::round_digits(prevPoseEulerAngles.pitch, 1);

			if (newPitch > prevPitch) {
				// The camera and user move up
				if (!isPitchUpLogged) {

					if (logCameraActions) {
						// Log yaw camera movement up
						mInformationWnindow->getUIRef().cameraActionsList->addItem("PITCH UP");
						counts = mInformationWnindow->getUIRef().cameraActionsList->count();
						mInformationWnindow->getUIRef().cameraActionsList->setCurrentRow(counts - 1);
					}

					if (logUserActions) {
						// Log yaw user movement up
						mInformationWnindow->getUIRef().userActionsList->addItem("LOOKING UP");
						counts = mInformationWnindow->getUIRef().userActionsList->count();
						mInformationWnindow->getUIRef().userActionsList->setCurrentRow(counts - 1);
					}

					isPitchUpLogged = true;
					isPitchDownLogged = false;
				}
			}
			// The camera and user move down
			else if (newPitch < prevPitch) {
				if (!isPitchDownLogged) {

					if (logCameraActions) {
						// Log depth camera movement down
						mInformationWnindow->getUIRef().cameraActionsList->addItem("PITCH DOWN");
						counts = mInformationWnindow->getUIRef().cameraActionsList->count();
						mInformationWnindow->getUIRef().cameraActionsList->setCurrentRow(counts - 1);
					}

					if (logUserActions) {
						// Log depth user movement down
						mInformationWnindow->getUIRef().userActionsList->addItem("LOOKING DOWN");
						counts = mInformationWnindow->getUIRef().userActionsList->count();
						mInformationWnindow->getUIRef().userActionsList->setCurrentRow(counts - 1);
					}

					isPitchUpLogged = false;
					isPitchDownLogged = true;
				}
			}
		}
		

		// THE CAMERA AND USER MOVEMENT IN DEPTH
		static short count = 0;		// if count is equal to 2 log zoom in else if count is equal to -2 log zoom out

		if (newWidth > prevWidth) {

			if (count < 2)	{ count++; return; }

			// The camera and user move forwards
			if (!isDepthForwardsLogged) {

				if (logCameraActions) {
					// Log depth camera movement forwards
					mInformationWnindow->getUIRef().cameraActionsList->addItem("ZOOM IN");
					counts = mInformationWnindow->getUIRef().cameraActionsList->count();
					mInformationWnindow->getUIRef().cameraActionsList->setCurrentRow(counts - 1);
				}

				if (logUserActions) {
					// Log depth user movement forwards
					mInformationWnindow->getUIRef().userActionsList->addItem("MOVING FORWARDS");
					counts = mInformationWnindow->getUIRef().userActionsList->count();
					mInformationWnindow->getUIRef().userActionsList->setCurrentRow(counts - 1);
				}

				isDepthForwardsLogged = true;
				isDepthBackwardsLogged = false;
			}
		}
		// The camera and user move backwards
		else if (newWidth < prevWidth) {

			if (count > -2)	{ count--; return; }

			if (!isDepthBackwardsLogged) {

				if (logCameraActions) {
					// Log depth camera movement backwards
					mInformationWnindow->getUIRef().cameraActionsList->addItem("ZOOM OUT");
					counts = mInformationWnindow->getUIRef().cameraActionsList->count();
					mInformationWnindow->getUIRef().cameraActionsList->setCurrentRow(counts - 1);
				}

				if (logUserActions) {
					// Log depth user movement backwards
					mInformationWnindow->getUIRef().userActionsList->addItem("MOVING BACKWARDS");
					counts = mInformationWnindow->getUIRef().userActionsList->count();
					mInformationWnindow->getUIRef().userActionsList->setCurrentRow(counts - 1);
				}

				isDepthForwardsLogged = false;
				isDepthBackwardsLogged = true;
			}
		}
}


// Get window aspect ratio
float RenderWindow::getWindowAspectRatio()
{
	return (float)mScreenWidth / mScreenHeight;
}