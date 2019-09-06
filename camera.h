/************************************************************************************/
/*																					*/
/*		File:			camera.h													*/
/*		Description:	This class manages camera operations						*/
/*		Creation date:	22.08.2015													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include "tools\mathlib.h"
#include <QtCore\qlist.h>
#include <float.h>


class Camera
{
public:

	// Constructor
	// The start position is at distance 2.0 on the z axis (to the viewer)
	// and the camera looks to 1.0 of the z-axis
	Camera() : mPosition(0.0f, 0.0f, 3.0f),
		mViewDirection(0.0f, 0.0f, -3.0f), mUp(0.0f, 1.0f, 0.0f),
		mPreviousYaw(-0.0), mPreviousPitch(-0.0), mPreviousWidth(0) {}

	// Destructor
	~Camera() {}

	// Set camera speed
	void setCameraSpeed(GLdouble cameraSpeed) { mCameraSpeed = cameraSpeed; }

	vec3 getVec() { return mViewDirection; }

	// World To View Transformation
	glm::mat4 getWorldToViewMatrix() const
	{
		return glm::lookAt(mPosition, mPosition + mViewDirection, mUp);
	}

	// Set camera position (default value of the up vector is [0.0f, 1.0f, 0.0f])
	void setCameraPosition(glm::vec3& position, glm::vec3& viewDirection,
		glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f))
	{
		mPosition = position;
		mViewDirection = viewDirection;
		mUp = up;
	}

	// Move the cam by the given values (rotation matrix calculation)
	void move(int width, float yaw, float pitch) {

		// Calculate the new new postion of the camera. If the old value is equal with
		// the new value then do мо movement backwards or forwards. In addition we
		// have to move the camera only if the difference of the old and new value is 
		// greater than 2. This is required for to remove the shake of the camera
		int faceRectDiff = Mathlib::abs_difference(mPreviousWidth, width);


		static int counter = 0;		// Reduces the camera shake in depth
		if (faceRectDiff > 2) {
			
			if (width > mPreviousWidth) {			// Move forwards (zoom in => width goes greater)
				if (counter < 1)	{ counter++; }
				else {
					mPosition.z += (mCameraSpeed + 0.5) * mViewDirection.z;
					mPreviousWidth = width;
				}
			}
			else if (width < mPreviousWidth) {		// Move backwards (zoom out => width goes lesser)
				if (counter > -1)	{ counter--; }
				else {
					mPosition.z -= (mCameraSpeed + 0.5) * mViewDirection.z;
					mPreviousWidth = width;
				}
			}
		}
		
		// Calculat the product for the rotation matrix yaw (rotation on Y-axis)
		// and for the rotation matrix pitch (rotation on X-axis). This product gives
		// us the full rotation on the two axis X and Y.
		mViewDirection = glm::mat3(glm::rotate(-yaw * mCameraSpeed, mUp)) * mViewDirection;
		glm::vec3 fullRotation = glm::cross(mViewDirection, mUp);
		mViewDirection = glm::mat3(glm::rotate(pitch * mCameraSpeed, fullRotation)) * mViewDirection;
		
		// If the coordinates of the view direction are NaN (not a number) 
		// then set the view direction to the origin
		if (_isnan(mViewDirection.x) /*|| _isnan(mViewDirection.y) || _isnan(mViewDirection.z)*/) {
			mViewDirection = vec3(0.0f, 0.0f, -3.0f);
		}

		// Round by one digit for accuracy
		float x = Mathlib::round_digits(mViewDirection.x, 1);
		float y = Mathlib::round_digits(mViewDirection.y, 1);
		float z = Mathlib::round_digits(mViewDirection.z, 1);
		mViewDirection = vec3(x, y, z);

		// Save the new values as previous
		mPreviousYaw = yaw;
		mPreviousPitch = pitch;
	}

	// Move camera left or right
	void moveLeftRight(float yaw)
	{
		mViewDirection = glm::mat3(glm::rotate(yaw * mCameraSpeed, vec3(0.0, 1.0, 0.0))) * mViewDirection;
		mPreviousYaw = yaw;
	}

	// Move camera up or down
	void moveUpDown(float pitch)
	{
		mViewDirection = glm::mat3(glm::rotate(pitch * mCameraSpeed, vec3(1.0, 0.0, 0.0))) * mViewDirection;
		mPreviousPitch = pitch;
	}

private:
	glm::vec3 mPosition;			// Position of the camera in space
	glm::vec3 mViewDirection;		// View direction of the camera
	glm::vec3 mUp;					// Up vector (orientation of the camera)
	float mPreviousYaw;				// Keep track of the old yaw value (x)
	float mPreviousPitch;			// Keep track of the old pitch value (y)
	int mPreviousWidth;				// Keep track of the old width of the face rect
	GLfloat mCameraSpeed;			// Speed of the camera
};

