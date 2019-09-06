/************************************************************************************/
/*																					*/
/*		File:			posedata.h													*/
/*		Description:	This structs represent the pose data we need for the head	*/
/*						tracking module												*/
/*		Creation date:	21.02.2016													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Associate																	*/
/*		Professor:		PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/


// ************************** Pose Euler Angles *********************************
// yaw: value in degrees, positive value indicates that the face is looking right
// pitch: value in degrees, poisitive value indicates that the face is looking up
// roll: value in degrees, positive value indicates that the face is leaning 
//		 towards the right shoulder
struct PoseEulerAngle
{
	float yaw, pitch, roll;		
};


// ************* Pose Quaternion ************************
// x: coordinate of the point, y: coordinate of the point 
// z: coordinate of the point, w: scaling factor
struct PoseQuaternion
{
	float x, y, z, w;	
};


// ************************** Head Position ****************************
// x, y, z are the 3D world coordination points of the face center point
// confidence: is the confidence value from 0 to 100
struct HeadPosition
{
	float x, y, z;
	int confidence;
};



