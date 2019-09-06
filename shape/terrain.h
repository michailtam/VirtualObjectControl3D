/************************************************************************************/
/*																					*/
/*		File:			terrain.h													*/
/*		Description:	This class represents a terrain. 							*/	
/*		Creation date:	28.09.2015													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once
#include <GL\glew.h>
#include "shapedata.h"
#include <string>
#include <glm\glm.hpp>

using namespace std;

class Terrain : public Shape
{
public:
	Terrain(float width, float depth, bool heightMapChoosen, float maxHeight, const string& name);
	~Terrain();

private:
	void generateVertices();
	void generateIndices();
	void generateNormals();
	bool loadHeightMap(const string& fileName);
	void calcHeightMapValues(float buffer[], unsigned int maxPixels);

	float mWidth;					// Width of the terrain (X-axis)
	float mDepth;					// Depth of the terrain (Z-axis)
	float mMaxHeight;				// Height of the terrain (Y-axis)
	GLint mChannels;				// Channels of the colors (example 4 = RGBA)
	unsigned char* mpImage;			// Image pointer
	vec2 mHeightMapDimensions;		// The dimensions of the height map
	bool mbHeightMapChoosen;		// Determines if a height map or a simple 
									// plane will be create
};

