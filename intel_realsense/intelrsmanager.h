/************************************************************************************/
/*																					*/
/*		File:			intelrsmanager.h											*/
/*		Description:	This file represents the Intel RealSense manager, who 		*/
/*						manages all the operations of the intel realsense			*/
/*						technology													*/
/*		Creation date:	16.02.2016													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Associate																	*/
/*		Professor:		PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/

#pragma once

#include "QtCore\qobject.h"
#include "pxcsensemanager.h"
#include "facetracking.h"
#include <map>

using namespace std;


class IntelRSManager : public QObject
{
	Q_OBJECT

public:
	IntelRSManager();
	~IntelRSManager();

	bool getCameraDeviceInfo(map<string, string>* deviceInfo);
	bool getInitStatus() { return mStatus; }
	bool checkIfCamConnected();					// Check if any cam is connected
	bool captureDataFromCam(QRect* rect,
		PoseEulerAngle* poseEulerAngles);		// Captures the data from the cam

private:
	PXCSenseManager* mSenseManager;				// The sense manager	
	PXCSession* mSession;						// The session 
	FaceTrackingModule* mFaceTrackingModule;	// The face tracking module
	PXCCapture::DeviceInfo mDeviceInfo;			// The device information
	bool mStatus;

	bool init();								// Inits the Intel RealSense Manager
	bool checkIfF200Cam();	// Checks if the cam is the F200 (front face camera)
	string getDeviceModel(PXCCapture::DeviceModel model);
	string getStreamType(PXCCapture::StreamType streamType);
	void releaseAll();
};

