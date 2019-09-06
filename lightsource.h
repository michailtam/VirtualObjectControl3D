/************************************************************************************/
/*																					*/
/*		File:			lightsource.h												*/
/*		Description:	This class represents the global light source like a lamp	*/
/*						or the sun													*/
/*		Creation date:	10.09.2015													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Associate																	*/
/*		Professor:		PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/

#pragma once
#include <glm\glm.hpp>

using glm::vec3;


class LightSource
{
public:

	// Constructor
	LightSource() : mLightPosition(0.0f, 3.0f, 0.0f) {}
	
	// Destructor
	~LightSource() {}

	vec3& getLightPosition() { return mLightPosition; }	// Get the position of the light

	// Change the light position
	void setLightPosition(vec3& newLightPosition) 
	{
		mLightPosition = newLightPosition;
	}

	// Set the properties of the light source
	void setAmbientLightColor(vec3& ambient)
	{
		mAmbientColor = ambient;
	}

	// Get ambient, diffuse light color
	vec3& getAmbientColor() { return mAmbientColor; }

private:
	vec3 mLightPosition;	// Light position
	vec3 mAmbientColor;		// Ambient color of the light source			
};

