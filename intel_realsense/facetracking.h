/************************************************************************************/
/*																					*/
/*		File:			facetracking.h												*/
/*		Description:	This class inherits from the base class Algorithm modules	*/
/*						and provides face tracking operations such as 				*/
/*						pose detection, face detection etc.							*/
/*		Creation date:	16.02.2016													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once
#include "algorithmmodule.h"
#include <QtCore\qrect.h>
#include "posedata.h"


class FaceTrackingModule : public AlgorithmModule
{
public:
	FaceTrackingModule(PXCSenseManager* senseManager);
	~FaceTrackingModule();

	// Face capture operations
	bool getInitStatus() { return mInitStatus; }
	bool getFaceDimensions(QRect* faceBoundaries = 0, float* faceDepth = 0);
	bool getFacePoseData(QRect* faceBoundaries = 0, PoseEulerAngle* eulerAngles = 0);
	bool getFaceCenterPoint(HeadPosition* headPosition);
	bool getRotationMatrix(double rotationMatrix[9]);

private:
	// The face module and the configuration
	PXCFaceConfiguration* mFaceConfig;
	PXCFaceModule* mFaceModule;

	bool init();
	PXCFaceData* getCurrentFaceData();	// Gets the current face data
};

