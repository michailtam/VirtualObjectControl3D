/************************************************************************************/
/*																					*/
/*		File:			renderer.h													*/
/*		Description:	This class manages all the drawing operations		 		*/
/*						to the OpenGL window										*/		
/*		Creation date:	13.01.2016													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once
#include <GL\glew.h>
#include "lightsource.h"
#include "shape\shapebuilder.h"
#include "camera.h"


// Forward declaration
class OpenGLManager;


class Renderer
{
public:
	Renderer();
	~Renderer();

	// Initialize the renderer
	void init(GLfloat aspectRatio, Camera* camera);
	void setup3DObjects();			// Setup all 3d objects we want to render
	void setupLightSource();		// Setup the light source
	void renderCube(GLuint programID);		// Render a cube
	void renderPyramid(GLuint programID);	// Render a pyramid
	void renderTerrain(GLuint programID);	// Render a terrain
	void renderLight(GLuint programID);		// Render a light
	Shape* getShape(const string& shapeName);	// Gets the shape by shape name
	// Updates the rotation interval
	void updateRotInterval(GLfloat rotCube, GLfloat rotPyramid);	
	void cleanup();					// Delete all saved shapes

private:
	LightSource mLightSource;			// Light source 
	vector<Shape*> mShapeList;			// Contains all the shapes
	OpenGLManager* mOpenGLManager;		// Manages all the OpenGL operations
	GLfloat mAspectRatio;				// Aspect ratio of the screen
	Camera* mCamera;					// Camera 
	GLfloat mRotIntervalCube;			// Rotation interval cube
	GLfloat mRotIntervalPyramid;		// Rotation interval pyramid
};

