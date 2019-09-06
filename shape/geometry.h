/************************************************************************************/
/*																					*/
/*		File:			geometry.h													*/
/*		Description:	This file contains the derived classes of the shape objects	*/
/*						(e.g. triangle, cube, ...)									*/
/*		Creation date:	15.08.2015													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Associate																	*/
/*		Professor:		PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/

#pragma once
#include <GL\glew.h>
#include "shapedata.h"
#include <glm\glm.hpp>

const GLuint VERTEX_PER_QUAD = 4;
const string CUBE_TEXTURE_FILE = "./res/cube.jpg";
const string PYRAMID_TEXTURE_FILE = "./res/pyramid02.jpg";

#pragma region _CUBE_

// This class contains the shape data of a cube
class Cube : public Shape
{
public:
	// Constructor
	Cube(const string& name)
	{ 
		setShapeName(name);		// Set name of the shape


		//						---- Position -----		------- Normals -------		-- Texture coord --
		// Top side of the cube
		addVertex(Vertex3D(vec3(-0.5f, 0.5f, 0.5f),		vec3(0.0f, 1.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 0
		addVertex(Vertex3D(vec3(0.5f, 0.5f, 0.5f),		vec3(0.0f, 1.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 1
		addVertex(Vertex3D(vec3(0.5f, 0.5f, -0.5f),		vec3(0.0f, 1.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 2
		addVertex(Vertex3D(vec3(-0.5f, 0.5f, -0.5f),		vec3(0.0f, 1.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 3
																
		// Back side of the cube								
		addVertex(Vertex3D(vec3(-0.5f, 0.5f, -0.5f),		vec3(0.0f, 0.0f, -1.0f),		vec2(0.0f, 1.0f)));		// 4
		addVertex(Vertex3D(vec3(0.5f, 0.5f, -0.5f),		vec3(0.0f, 0.0f, -1.0f),		vec2(1.0f, 1.0f)));		// 5
		addVertex(Vertex3D(vec3(0.5f, -0.5f, -0.5f),		vec3(0.0f, 0.0f, -1.0f),		vec2(1.0f, 0.0f)));		// 6
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, -0.5f)	,	vec3(0.0f, 0.0f, -1.0f),		vec2(0.0f, 0.0f)));		// 7
																
		// Right side of the cube								
		addVertex(Vertex3D(vec3(0.5f, 0.5f, -0.5f),		vec3(1.0f, 0.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 8
		addVertex(Vertex3D(vec3(0.5f, 0.5f, 0.5f),		vec3(1.0f, 0.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 9
		addVertex(Vertex3D(vec3(0.5f, -0.5f, 0.5f),		vec3(1.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 10
		addVertex(Vertex3D(vec3(0.5f, -0.5f, -0.5f),		vec3(1.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 11
																
		// Left side of the cube									
		addVertex(Vertex3D(vec3(-0.5f, 0.5f, 0.5f),		vec3(-1.0f, 0.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 12
		addVertex(Vertex3D(vec3(-0.5f, 0.5f, -0.5f),		vec3(-1.0f, 0.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 13
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, -0.5f)	,	vec3(-1.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 14
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, 0.5f),		vec3(-1.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 15
																
		// Front side of the cube								
		addVertex(Vertex3D(vec3(0.5f, 0.5f, 0.5f),		vec3(0.0f, 0.0f, 1.0f),		vec2(1.0f, 1.0f)));		// 16
		addVertex(Vertex3D(vec3(-0.5f, 0.5f, 0.5f),		vec3(0.0f, 0.0f, 1.0f),		vec2(0.0f, 1.0f)));		// 17
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, 0.5f),		vec3(0.0f, 0.0f, 1.0f),		vec2(0.0f, 0.0f)));		// 18
		addVertex(Vertex3D(vec3(0.5f, -0.5f, 0.5f),		vec3(0.0f, 0.0f, 1.0f),		vec2(1.0f, 0.0f)));		// 19

		// Bottom side of the cube								 
		addVertex(Vertex3D(vec3(0.5f, -0.5f, -0.5f),		vec3(0.0f, -1.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 20
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, -0.5f)	,	vec3(0.0f, -1.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 21
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, 0.5f),		vec3(0.0f, -1.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 22
		addVertex(Vertex3D(vec3(0.5f, -0.5f, 0.5f),		vec3(0.0f, -1.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 23	

		// Cube contains 36 indices
		GLushort indices[] =
		{
			0, 1, 2, 0, 2, 3,		// Top
			4, 5, 6, 4, 6, 7,		// Back
			8, 9, 10, 8, 10, 11,	// Right
			12, 13, 14, 12, 14, 15,	// Left
			16, 17, 18, 16, 18, 19,	// Front
			20, 22, 21, 20, 23, 22,	// Bottom	
		};

		addIndices(indices, NUM_ARRAY_ELEMENTS(indices));

		// Add a texture
		addTexture(CUBE_TEXTURE_FILE, GL_TEXTURE_2D, GL_TEXTURE0);
	}
};

#pragma endregion _CUBE_


#pragma region _PYRAMID_

// This class contains the shape data of a pyramid 
class Pyramid : public Shape
{
public:
	// Constructor
	Pyramid(const string& name)
	{ 
		setShapeName(name);		// Set name of the shape

		//						----- Position -----    ------- Normals -------		-- Texture coord --

		//  Back side of the pyramid
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, -0.5f),	vec3(0.0f, 0.0f, -1.0f),		vec2(1.0f, 0.0f)));	// 0
		addVertex(Vertex3D(vec3(0.0f, 1.0f, 0.0f),		vec3(0.0f, 0.0f, -1.0f),		vec2(0.5f, 1.0f)));	// 1
		addVertex(Vertex3D(vec3(0.5f, -0.5f, -0.5f),		vec3(0.0f, 0.0f, -1.0f),		vec2(0.0f, 0.0f)));	// 2
														vec3(0.0f, 0.0f, -1.0f),		
		// Right side of the pyramid						
		addVertex(Vertex3D(vec3(0.5f, -0.5f, -0.5f),		vec3(1.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));	// 3
		addVertex(Vertex3D(vec3(0.0f, 1.0f, 0.0f),		vec3(1.0f, 0.0f, 0.0f),		vec2(0.5f, 1.0f)));	// 4
		addVertex(Vertex3D(vec3(0.5f, -0.5f, 0.5f),		vec3(1.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));	// 5
														vec3(1.0f, 0.0f, 0.0f),		
		// Left side of the pyramid							
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, 0.5f),		vec3(-1.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));	// 6
		addVertex(Vertex3D(vec3(0.0f, 1.0f, 0.0f),		vec3(-1.0f, 0.0f, 0.0f),		vec2(0.5f, 1.0f)));	// 7
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, -0.5f),	vec3(-1.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));	// 8
														vec3(-1.0f, 0.0f, 0.0f),		
		// Front side of the the pyramid						
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, 0.5f),		vec3(0.0f, 0.0f, 1.0f),		vec2(0.0f, 0.0f)));	// 9
		addVertex(Vertex3D(vec3(0.5f, -0.5f, 0.5f),		vec3(0.0f, 0.0f, 1.0f),		vec2(1.0f, 0.0f)));	// 10
		addVertex(Vertex3D(vec3(0.0f, 1.0f, 0.0f),		vec3(0.0f, 0.0f, 1.0f),		vec2(0.5f, 1.0f)));	// 11
														vec3(0.0f, 0.0f, 1.0f),		
		// Bottom side of the pyramid						
		addVertex(Vertex3D(vec3(0.5f, -0.5f, -0.5f),		vec3(0.0f, -1.0f, 0.0f),		vec2(1.0f, 0.0f)));	// 12
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, -0.5f),	vec3(0.0f, -1.0f, 0.0f),		vec2(0.5f, 1.0f)));	// 13
		addVertex(Vertex3D(vec3(-0.5f, -0.5f, 0.5f),		vec3(0.0f, -1.0f, 0.0f),		vec2(0.0f, 0.0f)));	// 14
		addVertex(Vertex3D(vec3(0.5f, -0.5f, 0.5f),		vec3(0.0f, -1.0f, 0.0f),		vec2(0.0f, 0.0f)));	// 15

		// Pyramid contains 18 indices

		GLushort indices[] =
		{
			0, 1, 2,				// Back  
			3, 4, 5,				// Right
			6, 7, 8,				// Left
			9, 10, 11,				// Front
			12, 14, 13, 12, 15, 14	// Bottom
		};

		addIndices(indices, NUM_ARRAY_ELEMENTS(indices));

		// Add a texture
		addTexture(PYRAMID_TEXTURE_FILE, GL_TEXTURE_2D, GL_TEXTURE1);
	}
};

#pragma endregion _PYRAMID_


/*#pragma region _SKYBOX_

// This class contains the shape data of a skybox. A skybox is a cubemap which
// which displays the environment of a scene. The skybox positions x,y,z are 
// set to 1.0 or -1.0, cause of the maximum values we can reach in normalized 
// device space (NDS)
class SkyBox : public Shape
{
public:
	// Constructor
	SkyBox(const string& name)
	{
		setShapeName(name);		// Set name of the shape

		//						---- Position -----		------- Normals -------		-- Texture coord --
		// Top side of the skybox
		addVertex(Vertex3D(vec3(-1.0f, 1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 0
		addVertex(Vertex3D(vec3(1.0f, 1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 1
		addVertex(Vertex3D(vec3(1.0f, 1.0f, -1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 2
		addVertex(Vertex3D(vec3(-1.0f, 1.0f, -1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 3

		// Back side of the skybox								
		addVertex(Vertex3D(vec3(-1.0f, 1.0f, -1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 4
		addVertex(Vertex3D(vec3(1.0f, 1.0f, -1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 5
		addVertex(Vertex3D(vec3(1.0f, -1.0f, -1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 6
		addVertex(Vertex3D(vec3(-1.0f, -1.0f, -1.0f),	vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 7

		// Right side of the skybox								
		addVertex(Vertex3D(vec3(1.0f, 1.0f, -1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 8
		addVertex(Vertex3D(vec3(1.0f, 1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 9
		addVertex(Vertex3D(vec3(1.0f, -1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 10
		addVertex(Vertex3D(vec3(1.0f, -1.0f, -1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 11

		// Left side of the skybox									
		addVertex(Vertex3D(vec3(-1.0f, 1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 12
		addVertex(Vertex3D(vec3(-1.0f, 1.0f, -1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 13
		addVertex(Vertex3D(vec3(-1.0f, -1.0f, -1.0f),	vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 14
		addVertex(Vertex3D(vec3(-1.0f, -1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 15

		// Front side of the skybox								
		addVertex(Vertex3D(vec3(1.0f, 1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 16
		addVertex(Vertex3D(vec3(-1.0f, 1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 17
		addVertex(Vertex3D(vec3(-1.0f, -1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 18
		addVertex(Vertex3D(vec3(1.0f, -1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 19

		// Bottom side of the skybox								 
		addVertex(Vertex3D(vec3(1.0f, -1.0f, -1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 1.0f)));		// 20
		addVertex(Vertex3D(vec3(-1.0f, -1.0f, -1.0f),	vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 1.0f)));		// 21
		addVertex(Vertex3D(vec3(-1.0f, -1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(0.0f, 0.0f)));		// 22
		addVertex(Vertex3D(vec3(1.0f, -1.0f, 1.0f),		vec3(0.0f, 0.0f, 0.0f),		vec2(1.0f, 0.0f)));		// 23	

		// Skybox contains 36 indices
		GLushort indices[] =
		{
			0, 1, 2, 0, 2, 3,		// Top
			4, 5, 6, 4, 6, 7,		// Back
			8, 9, 10, 8, 10, 11,	// Right
			12, 13, 14, 12, 14, 15,	// Left
			16, 17, 18, 16, 18, 19,	// Front
			20, 22, 21, 20, 23, 22,	// Bottom	
		};

		addIndices(indices, NUM_ARRAY_ELEMENTS(indices));

		// Add a texture
		addTexture(CUBE_TEXTURE_FILE, GL_TEXTURE_2D, GL_TEXTURE0);
	}
};

#pragma endregion _SKYBOX_*/
