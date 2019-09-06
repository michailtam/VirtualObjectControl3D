/************************************************************************************/
/*																					*/
/*		File:			shapebuilder.h												*/
/*		Description:	This class manages the shape building (e.g. triangles, 	 	*/
/*						cubes, ...)													*/
/*		Creation date:	15.08.2015													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once
#include <GL\glew.h>
#include "shape\shapedata.h"
#include <string>
#include "shape\geometry.h"
#include <glm\glm.hpp>
#include "terrain.h"


class ShapeBuilder
{
public:
	ShapeBuilder();
	~ShapeBuilder();

	// Create all shapes
	static Shape* createShape(short type, const string& shapeName,
		float width=0.0f, float depth=0.0f, 
		bool heightMapChoosen = false, float maxHeight=10.0f)
	{
		Shape* shape = 0;

		// Check what kind of shape we want to create
		switch (type) {
			case 0:	// Cube
				shape = new Cube(shapeName);
				break;
			case 1:	// Pyramid
				shape = new Pyramid(shapeName);
				break;
			case 2:	// Terrain
				shape = new Terrain(width, depth, heightMapChoosen, maxHeight, shapeName);
				break;
		}

		return shape;
	}
};

