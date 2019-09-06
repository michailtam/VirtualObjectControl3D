#include "FaceTracking.h"


// Constructor
FaceTrackingModule::FaceTrackingModule(PXCSenseManager* senseManager)
{
	// Save the sense manager object
	mSenseManager = senseManager;

	// Inits the face tracking module
	mInitStatus = init();
}

// Destructor
FaceTrackingModule::~FaceTrackingModule()
{
	
}

// Inits the face tracking module
bool FaceTrackingModule::init()
{
	// Retrieve the face module
	mFaceModule = mSenseManager->QueryFace();
	if (mFaceModule == NULL) return false;

	// Configure the face module
	mFaceConfig = mFaceModule->CreateActiveConfiguration();
	if (mFaceConfig == NULL) return false;

	// Set face module configuration properties
	mFaceConfig->detection.isEnabled = true;		// Enable face location
	mFaceConfig->pose.isEnabled = true;			// Enable pose detection
	mFaceConfig->EnableAllAlerts();

	mFaceConfig->ApplyChanges();

	return true;
}

// Get the current face data
PXCFaceData* FaceTrackingModule::getCurrentFaceData()
{
	// Returns the face data for face tracking output
	PXCFaceData* faceData = mFaceModule->CreateOutput();
	if (faceData == NULL) return NULL;

	return faceData;
}

// Get the dimensions of the face
bool FaceTrackingModule::getFaceDimensions(QRect* faceBoundaries, float* faceDepth)
{
	bool status = false;

	PXCFaceData* faceData = getCurrentFaceData();
	faceData->Update();

	// If there are detected faces
	if (faceData->QueryNumberOfDetectedFaces() > 0) {
		
		// Get the detected face
		PXCFaceData::Face* trackedFace = faceData->QueryFaceByIndex(0);
		if (trackedFace == 0)	return false;
		PXCFaceData::DetectionData* detectionData = trackedFace->QueryDetection();
		if (detectionData == 0)	return false;

		// Get the bounding rectangle of the face in pixels
		if (faceBoundaries != 0) {
			PXCRectI32 boundaries;
			detectionData->QueryBoundingRect(&boundaries);
			faceBoundaries->setRect(boundaries.x, boundaries.y, boundaries.w, boundaries.h);
			status = true;
		}

		// Get the average face depth to the camera in mm
		if (faceDepth != 0) {
			pxcF32 averageFaceDepth;
			detectionData->QueryFaceAverageDepth(&averageFaceDepth);
			faceDepth = &averageFaceDepth;
			status = true;
		}
		if (status)	return true;
	}
	return false;
}

// Get the face pose data
bool FaceTrackingModule::getFacePoseData(QRect* faceBoundaries, PoseEulerAngle* eulerAngles)
{
	bool status = false;

	PXCFaceData* faceData = getCurrentFaceData();
	if (faceData == NULL)	return false;
	faceData->Update();

	// If there are detected faces
	if (faceData->QueryNumberOfDetectedFaces() > 0) {

		// Get the detected face
		PXCFaceData::Face* trackedFace = faceData->QueryFaceByIndex(0);
		PXCFaceData::PoseData* poseData = trackedFace->QueryPose();
		if (poseData == 0) return false;

		// Get the pose angles (Euler angles)
		if (&eulerAngles != 0) {
			PXCFaceData::PoseEulerAngles poseAngles;
			poseData->QueryPoseAngles(&poseAngles);

			eulerAngles->yaw = poseAngles.yaw;		// Yaw
			eulerAngles->pitch = poseAngles.pitch;	// Pitch
			eulerAngles->roll = poseAngles.roll;		// Roll
			status = true;
		}

		// Get the bounding rectangle of the face in pixels
		PXCFaceData::DetectionData* detectionData = trackedFace->QueryDetection();
		if (detectionData == 0)	return false;
		
		if (faceBoundaries != 0) {
			PXCRectI32 boundaries;
			detectionData->QueryBoundingRect(&boundaries);
			faceBoundaries->setRect(boundaries.x, boundaries.y, boundaries.w, boundaries.h);
			status = true;
		}

		if (status)	return true;
	}
	return false;
}

// Get the face center point
bool FaceTrackingModule::getFaceCenterPoint(HeadPosition* headPosition)
{
	PXCFaceData* faceData = getCurrentFaceData();
	if (faceData == NULL)	return false;
	faceData->Update();

	// If there are detected faces
	if (faceData->QueryNumberOfDetectedFaces() > 0) {
		
		// Get the detected face
		PXCFaceData::Face* trackedFace = faceData->QueryFaceByIndex(0);
		PXCFaceData::PoseData* poseData = trackedFace->QueryPose();
		if (poseData == 0) return false;

		PXCFaceData::HeadPosition headPos;
		poseData->QueryHeadPosition(&headPos);

		headPosition->x = headPos.headCenter.x;
		headPosition->y = headPos.headCenter.y;
		headPosition->z = headPos.headCenter.z;
		headPosition->confidence = headPos.confidence;

		return true;
	}
	return false;
}

// Get the rotation matrix 
bool FaceTrackingModule::getRotationMatrix(double rotationMatrix[9])
{
	PXCFaceData* faceData = getCurrentFaceData();
	if (faceData == NULL)	return false;
	faceData->Update();

	// If there are detected faces
	if (faceData->QueryNumberOfDetectedFaces() > 0) {

		// Get the detected face
		PXCFaceData::Face* trackedFace = faceData->QueryFaceByIndex(0);
		PXCFaceData::PoseData* poseData = trackedFace->QueryPose();
		if (poseData == 0) return false;

		poseData->QueryRotationMatrix(rotationMatrix);
		return true;
	}
	return false;
}