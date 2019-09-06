#include "intelrsmanager.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

const int CAPTURE_TIMEOUT = 1000;	// 1000ms = 1sec


// Constructor
IntelRSManager::IntelRSManager()
{
	// Init the Intel RealSense manager
	mStatus = init();
}

// Destructor
IntelRSManager::~IntelRSManager()
{
	releaseAll();	// Release all reserved memory
}

// Configure the Intel RealSense module
bool IntelRSManager::init()
{
	// Create the sense manager. The sense manager is the main instance 
	// who manages I/Os and the algorithm modules
	mSenseManager = PXCSenseManager::CreateInstance();
	mSession = mSenseManager->QuerySession();
	
	// Check if camera device is connected
	if (!checkIfCamConnected())	return false;

	// Check if the camera is the F200 from Intel
	if (!checkIfF200Cam())	return false;

	// Enable the face module
	mSenseManager->EnableFace();

	// Create and init the face tracking module
	mFaceTrackingModule = new FaceTrackingModule(mSenseManager);
	if (!mFaceTrackingModule->getInitStatus())	return false;

	// Start the capture process
	if (mSenseManager->Init() < PXC_STATUS_NO_ERROR)
		return false;

	return true;
}

// Capture new face data from the cam
bool IntelRSManager::captureDataFromCam(QRect* rect, PoseEulerAngle* poseEulerAngles)
{
	// Set all capture flags to false. These flags are needed cause the complete 
	// capture process works asynchronous 
	bool facePoseDataCaptured = false;

	// Wait till new frame is available
	if (mSenseManager->AcquireFrame(true, CAPTURE_TIMEOUT) >= PXC_STATUS_NO_ERROR) {

		// Capture the face pose data
		if (mFaceTrackingModule->getFacePoseData(rect, poseEulerAngles) && !facePoseDataCaptured)
			facePoseDataCaptured = true;

		// Check if ALL captured processes are completed
		if (facePoseDataCaptured) {
			mSenseManager->ReleaseFrame();
			return true;
		}
		else {
			mSenseManager->ReleaseFrame();
		}
	} 

	// Check if the cam data were captured without problems and return the status
	if (facePoseDataCaptured) {
		mSenseManager->ReleaseFrame();
		return true;
	}
	else return false;
}

// Check if camera is connected to usb port
bool IntelRSManager::checkIfCamConnected()
{
	// Create an instance of the capture module 
	PXCCapture* capture;
	pxcStatus status = mSession->CreateImpl<PXCCapture>(&capture);
	if (status < PXC_STATUS_NO_ERROR) return false;
	
	// Check if there is any device connected
	pxcI32 num = capture->QueryDeviceNum();
	if (num == 0)	return false;

	// Get the device information
	status = capture->QueryDeviceInfo(0, &mDeviceInfo);
	if (status < PXC_STATUS_NO_ERROR)	return false;
	
	return true;
}

// Checks if the installed camera is the front facing cam f200 from Intel
bool IntelRSManager::checkIfF200Cam()
{
	// Get the coordinate system setting
	PXCSession::CoordinateSystem cs = mSession->QueryCoordinateSystem();

	// Check if coordinate system is for the front facing camera F200
	if (cs & PXCSession::COORDINATE_SYSTEM_FRONT_DEFAULT) {
		return true;
	}
	else
		return false;
}

// Gets the device information 
bool IntelRSManager::getCameraDeviceInfo(map<string, string>* deviceInfo)
{
	pxcCHAR* devName = mDeviceInfo.name;					// Device name
	PXCCapture::DeviceModel devModel = mDeviceInfo.model;	// Device model
	pxcCHAR* devSerial = mDeviceInfo.serial;				// Device serial
	PXCCapture::StreamType devStreamType = mDeviceInfo.streams;	// Supported streams 

	// Convert all to string
	wstring ws1(devName);
	string sDeviceName(ws1.begin(), ws1.end());
	string sDeviceModel = getDeviceModel(mDeviceInfo.model);
	wstring ws2(devSerial);
	string sDeviceSerial(ws2.begin(), ws2.end());
	string sStreamTypes = getStreamType(mDeviceInfo.streams);

	// Add all strings to a map (key: description, value: string of the info)
	deviceInfo->insert(pair<string, string>("Device Name", sDeviceName));
	deviceInfo->insert(pair<string, string>("Device Model", sDeviceModel));
	deviceInfo->insert(pair<string, string>("Device Serial", sDeviceSerial));
	deviceInfo->insert(pair<string, string>("Device Streams", sStreamTypes));

	return true;
}

// Get the device model as string
string IntelRSManager::getDeviceModel(PXCCapture::DeviceModel model)
{
	switch (model)
	{
		case 0x0020000E:
			return "DEVICE MODEL F200";
		case 0x0020000F:
			return "DEVICE MODEL R200";
		case 0x00200010:
			return "DEVICE MODEL SR300";
		case 0x0020001F:
			return "DEVICE MODEL R200 ENHANCED";
		case 0x00000000:
			return "GENERIC OR UNKNOWN DEVICE ";
	}
	return NULL;
}

// Gets the supported stream types
string IntelRSManager::getStreamType(PXCCapture::StreamType streamType)
{
	string sTmp;

	short overflow = streamType & 1;	// Check for color stream
	if (overflow & 0x0001)				
		sTmp += "STREAM TYPE COLOR";
	
	overflow = streamType & 2;			// Check for depth stream
	if (overflow & 0x0002)			
		sTmp += "%STREAM TYPE DEPTH";

	overflow = streamType & 4;			// Check for ir stream
	if (overflow & 0x0004)			
		sTmp += "%STREAM TYPE IR";

	overflow = streamType & 8;			// Check for stereoscopic left intensity image
	if (overflow & 0x0008)			
		sTmp += "%STREAM TYPE LEFT";	

	overflow = streamType & 10;			// Check for stereoscopic right intensity image
	if (overflow & 0x0010)			
		sTmp += "%STREAM TYPE RIGHT";
	
	overflow = streamType & 1;			// Undefined stream
	if (overflow & 0)				
		sTmp = "UNDEFINED STREAM";		

	return sTmp;
}

// Release all the reserved memory and resources
void IntelRSManager::releaseAll()
{
	// VERY IMPORTANT: 
	// It is not allowed to clean the sheltering intel realsense objects
	// like facemodule, handmodule etc. cause the sense manager relases
	// all reserved memories itself.
	if (mSenseManager)
	{
		mSenseManager->Close();
		mSenseManager->Release();
		mSenseManager = NULL;

		delete mFaceTrackingModule;
	}
}
