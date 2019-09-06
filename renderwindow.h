/************************************************************************************/
/*																					*/
/*		File:			renderwindow.h												*/
/*		Description:	This class contains the OpenGL window in which we will  	*/
/*						render our 3d objects										*/
/*		Creation date:	15.08.2015													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Associate																	*/
/*		Professor:		PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/

#pragma once
#include "ui_renderwindow.h"
#include "shader\glslshadermanager.h"
#include <QtWidgets\qopenglwidget.h>
#include "renderer.h"
#include "camera.h"
#include <string>
#include "intel_realsense\intelrsmanager.h"
#include "informationwindow.h"

using namespace std;

class Renderer;


class RenderWindow : public QOpenGLWidget
{
	Q_OBJECT

public:
	RenderWindow(GLint screenWidth, GLint screenHeight, InformationWindow* informationWnindow, QWidget* parent = 0);
	~RenderWindow();				

	float getWindowAspectRatio();		// Get the windows aspect ratio

protected:
	void initializeGL();				// Init method of OpenGL
	void paintGL();						// Paint method of OpenGL	
	void captureIRSCameraData();		// Gets all the new needed face data
	
private:
	// Log the user and camera actions ont the user interface (UI)
	void logDataOnUI(int newWidth, int prevWidth,
		PoseEulerAngle newPoseEulerAngles, PoseEulerAngle prevPoseEulerAngles);

	Ui::RenderWindowUI ui;				// User interface reference

	int mScreenWidth;					// Desktop width
	int mScreenHeight;					// Desktop height
	float mAspectRatio;					// Aspect ratio of the viewport
	GLSLShaderManager mGLSLShaderManager;	// Manages all the shader operations
	Camera mCamera;						// Camera of the scene
	Renderer* mRenderer;				// Manages all drawing operations
	IntelRSManager mIntelRSManager;		// Intel RealSense Manager

	QRect mFaceRect;					// Contains the face rect dimensions
	PoseEulerAngle mPoseEulerAngles;	// Contains the face pose angles
	PoseQuaternion mPoseQuaternion;		// Contains the quaternion data of the face
	HeadPosition mHeadPosition;			// Contains the world coordinates of the head position

	InformationWindow* mInformationWnindow;	// For referencing to the ui controlls of the information window

// Signals and Slots
signals:

private slots:

};

