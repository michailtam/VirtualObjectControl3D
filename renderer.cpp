#include "renderer.h"
#include "openglmanager.h"
#include "shape\geometry.h"
#include "shape\terrain.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <string>

using namespace std;
using glm::mat4;
using glm::vec3;

// Shape names 
const string CUBE_NAME = "cube01";
const string PYRAMID_NAME = "pyramid01";
const string TERRAIN_NAME = "terrain01";

// Colors in RGB mode
struct Color {
	vec3 red = vec3(1.0f, 0.0f, 0.0f);			// Red
	vec3 green = vec3(0.0f, 1.0f, 0.0f);		// Green
	vec3 blue = vec3(0.0f, 0.0f, 1.0f);			// Blue
	vec3 white = vec3(1.0f, 1.0f, 1.0f);		// White
	vec3 grey = vec3(0.2f, 0.2f, 0.2f);			// Grey
	vec3 black = vec3(0.0f, 0.0f, 0.0f);		// black
} COLOR;

const GLuint VERTEX_BYTE_SIZE = 8 * sizeof(GL_FLOAT);		// Byte size of one Vertex3D object in VBO
const GLuint NORMALS_BYTE_OFFSET = 3 * sizeof(GL_FLOAT);	// Offset to the normals in VBO
const GLuint TEXCOORDS_BYTE_OFFSET = 6 * sizeof(GL_FLOAT);	// Offset to the texture coordinates in VBO

// Constants for the view frustum
const GLfloat FOV = 64.0f;			// Field of view
const GLfloat NEAR_PLANE = 0.1f;	// Near plane
const GLfloat FAR_PLANE = 40.0f;	// Far plane

// Enum shape types
enum ShapeType { CUBE = 0, PYRAMID, TERRAIN };


// Constructor
Renderer::Renderer()
{
	// Create the OpenGLManager who manages all the GPU operations 
	// and initializes the OpenGL preferences
	mOpenGLManager = new OpenGLManager();
}

// Destructor
Renderer::~Renderer()
{
	mOpenGLManager->cleanup();
	delete mOpenGLManager;
	cleanup();
}

// Setup the Renderer
void Renderer::init(GLfloat aspectRatio, Camera* camera)
{
	mAspectRatio = aspectRatio;
	mCamera = camera;

	// Setup 3D objects and light source
	setup3DObjects();
	setupLightSource();
}

// Setup the 3D objects we want to render
void Renderer::setup3DObjects()
{
	Cube* cube = (Cube*)ShapeBuilder::createShape(CUBE, CUBE_NAME);
	Pyramid* pyramid = (Pyramid*)ShapeBuilder::createShape(PYRAMID, PYRAMID_NAME);
	Terrain* terrain = (Terrain*)ShapeBuilder::createShape(TERRAIN, TERRAIN_NAME, 10.0f, 12.0f, false, 100.0f);

	// Keep all the shapes we create in a list
	mShapeList.push_back(cube);
	mShapeList.push_back(pyramid);
	mShapeList.push_back(terrain);

	// Now we are creating vertex and index buffers for the cube, pyramid and terrain
	// and store the appropriate data in them. After that we setup the vertex array attributes
	// and bind them including the buffers to the associated VAO
	GLsizeiptr cubeVertexBufferSize = cube->getVertexBufferSize();
	GLsizeiptr cubeIndexBufferSize = cube->getIndexBufferSize();
	GLsizeiptr pyramidVertexBufferSize = pyramid->getVertexBufferSize();
	GLsizeiptr pyramidIndexBufferSize = pyramid->getIndexBufferSize();
	GLsizeiptr terrainVertexBufferSize = terrain->getVertexBufferSize();
	GLsizeiptr terrainIndexBufferSize = terrain->getIndexBufferSize();

	// Create the vertex and index buffers and store the cube and pyramid data in them
	GLuint vertexBufferID = mOpenGLManager->createBuffer(GL_ARRAY_BUFFER, cubeVertexBufferSize + pyramidVertexBufferSize, GL_DYNAMIC_DRAW);
	mOpenGLManager->storeDataInBuffer(vertexBufferID, GL_ARRAY_BUFFER, 0, cubeVertexBufferSize, cube->getVertices());
	mOpenGLManager->storeDataInBuffer(vertexBufferID, GL_ARRAY_BUFFER, cubeVertexBufferSize, pyramidVertexBufferSize, pyramid->getVertices());

	GLuint indexBufferID = mOpenGLManager->createBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBufferSize + pyramidIndexBufferSize, GL_STATIC_DRAW);
	mOpenGLManager->storeDataInBuffer(indexBufferID, GL_ELEMENT_ARRAY_BUFFER, 0, cubeIndexBufferSize, cube->getIndices());
	mOpenGLManager->storeDataInBuffer(indexBufferID, GL_ELEMENT_ARRAY_BUFFER, cubeIndexBufferSize, pyramidIndexBufferSize, pyramid->getIndices());

	// Create the terrain buffer and store the terrain data in it
	GLuint vertexTerrainBufferID = mOpenGLManager->createBuffer(GL_ARRAY_BUFFER, terrainVertexBufferSize, GL_STATIC_DRAW);
	mOpenGLManager->storeDataInBuffer(vertexTerrainBufferID, GL_ARRAY_BUFFER, 0, terrainVertexBufferSize, terrain->getVertices());
	GLuint indexTerrainBufferID = mOpenGLManager->createBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIndexBufferSize, GL_STATIC_DRAW);
	mOpenGLManager->storeDataInBuffer(indexTerrainBufferID, GL_ELEMENT_ARRAY_BUFFER, 0, terrainIndexBufferSize, terrain->getIndices());


	// Attribute Setup

	// CUBE
	GLuint vertexVAO = mOpenGLManager->createVAO(CUBE_NAME);
	mOpenGLManager->bindVAO(vertexVAO);
	mOpenGLManager->bindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	mOpenGLManager->setupVertexArrayAttribute(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
	mOpenGLManager->setupVertexArrayAttribute(1, 2, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (GLvoid*)(TEXCOORDS_BYTE_OFFSET));
	mOpenGLManager->setupVertexArrayAttribute(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (GLvoid*)(NORMALS_BYTE_OFFSET));
	mOpenGLManager->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	mOpenGLManager->bindVAO(0);

	// PYRAMID
	vertexVAO = mOpenGLManager->createVAO(PYRAMID_NAME);
	mOpenGLManager->bindVAO(vertexVAO);
	mOpenGLManager->bindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	mOpenGLManager->setupVertexArrayAttribute(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (GLvoid*)(cubeVertexBufferSize));
	mOpenGLManager->setupVertexArrayAttribute(1, 2, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (GLvoid*)(cubeVertexBufferSize + TEXCOORDS_BYTE_OFFSET));
	mOpenGLManager->setupVertexArrayAttribute(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (GLvoid*)(cubeVertexBufferSize + NORMALS_BYTE_OFFSET));
	mOpenGLManager->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	mOpenGLManager->bindVAO(0);

	// TERRAIN
	vertexVAO = mOpenGLManager->createVAO(TERRAIN_NAME);
	mOpenGLManager->bindVAO(vertexVAO);
	mOpenGLManager->bindBuffer(GL_ARRAY_BUFFER, vertexTerrainBufferID);
	mOpenGLManager->setupVertexArrayAttribute(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
	mOpenGLManager->setupVertexArrayAttribute(1, 2, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (GLvoid*)(TEXCOORDS_BYTE_OFFSET));
	mOpenGLManager->setupVertexArrayAttribute(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (GLvoid*)(NORMALS_BYTE_OFFSET));
	mOpenGLManager->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexTerrainBufferID);
	mOpenGLManager->bindVAO(0);
}

// Setup the light source
void Renderer::setupLightSource()
{
	// Set the light source properties
	vec3 lightPos(0.0f, 4.0f, 1.0f);
	mLightSource.setAmbientLightColor(COLOR.white);
	mLightSource.setLightPosition(lightPos);
}

// Render a cube
void Renderer::renderCube(GLuint programID)
{
	// Get the cube data
	Shape* cube = getShape(CUBE_NAME);

	mat4 transformMatrix;

	cube->bindTexture(GL_TEXTURE0);		// Bind the texture of the cube
	GLuint sampler2DUniformLocation = mOpenGLManager->getUniformLocation(programID, "texturemap");
	mOpenGLManager->setUniform1i(sampler2DUniformLocation, 0);	// Send texture data to the GPU

	GLuint vaoID = mOpenGLManager->getVAO(CUBE_NAME);
	mOpenGLManager->bindVAO(vaoID);
	transformMatrix = mOpenGLManager->getTransformationMatrix(transformMatrix, vec3(1.0f, 0.0f, 0.0f),
		mRotIntervalCube, vec3(-2.0f, 1.0f, -1.0f), vec3(1.5f));
	mat4 projectionMatrix = glm::perspective(FOV, mAspectRatio, NEAR_PLANE, FAR_PLANE);
	mat4 MVP = projectionMatrix * mCamera->getWorldToViewMatrix() * transformMatrix;

	GLuint matrixID = mOpenGLManager->getUniformLocation(programID, "MVP");
	mOpenGLManager->setUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	GLuint modelToWorldMatrixUniformLocation = mOpenGLManager->getUniformLocation(programID, "MtoW");
	mOpenGLManager->setUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE, &transformMatrix[0][0]);

	GLsizei size = cube->getIndexCount();
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);
	mOpenGLManager->bindVAO(0);
}

// Render a pyramid
void Renderer::renderPyramid(GLuint programID)
{
	// Get the cube and shape data
	Shape* cube = getShape(CUBE_NAME);
	Shape* pyramid = getShape(PYRAMID_NAME);

	mat4 transformMatrix;

	pyramid->bindTexture(GL_TEXTURE1);	// Bind the texture of the pyramid
	GLuint sampler2DUniformLocation = mOpenGLManager->getUniformLocation(programID, "texturemap");
	mOpenGLManager->setUniform1i(sampler2DUniformLocation, 1);	// Send texture data to the GPU

	GLuint vaoID = mOpenGLManager->getVAO(PYRAMID_NAME);
	mOpenGLManager->bindVAO(vaoID);
	transformMatrix = mOpenGLManager->getTransformationMatrix(mat4(), vec3(0.0f, 1.0f, 0.0f), mRotIntervalPyramid,
		vec3(3.0f, 0.0f, -3.0f), vec3(2.0f));
	mat4 projectionMatrix = glm::perspective(FOV, mAspectRatio, NEAR_PLANE, FAR_PLANE);
	mat4 MVP = projectionMatrix * mCamera->getWorldToViewMatrix() * transformMatrix;

	GLuint matrixID = mOpenGLManager->getUniformLocation(programID, "MVP");
	mOpenGLManager->setUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	GLuint modelToWorldMatrixUniformLocation = mOpenGLManager->getUniformLocation(programID, "MtoW");
	mOpenGLManager->setUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE, &transformMatrix[0][0]);

	GLsizei size = pyramid->getIndexCount();
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, (GLvoid*)(cube->getIndexBufferSize()));
	mOpenGLManager->bindVAO(0);
}

// Render a terrain
void Renderer::renderTerrain(GLuint programID)
{
	// Get the terrain data
	Shape* terrain = getShape(TERRAIN_NAME);

	mat4 transformMatrix;

	terrain->bindTexture(GL_TEXTURE2);	// Bind the texture of the terrain
	GLuint sampler2DUniformLocation = mOpenGLManager->getUniformLocation(programID, "texturemap");
	mOpenGLManager->setUniform1i(sampler2DUniformLocation, 2);	// Send texture data to the GPU

	GLuint vaoID = mOpenGLManager->getVAO(TERRAIN_NAME);
	mOpenGLManager->bindVAO(vaoID);
	transformMatrix = mOpenGLManager->getTransformationMatrix(mat4(), vec3(1.0f, 0.0f, 0.0f), 0.2f,
		vec3(0.0f, -1.0f, -1.0f));
	mat4 projectionMatrix = glm::perspective(FOV, mAspectRatio, NEAR_PLANE, FAR_PLANE);

	mat4 MVP = projectionMatrix * mCamera->getWorldToViewMatrix() * transformMatrix;

	GLuint matrixID = mOpenGLManager->getUniformLocation(programID, "MVP");
	mOpenGLManager->setUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	GLuint modelToWorldMatrixUniformLocation = mOpenGLManager->getUniformLocation(programID, "MtoW");
	mOpenGLManager->setUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE, &transformMatrix[0][0]);

	// Set a blend color of dark blue for the terrain
	vec3 blendcolor = vec3(0.3f, 0.7f, 1.0f);
	GLuint blendColorUniformLocation = mOpenGLManager->getUniformLocation(programID, "blendcolor");
	mOpenGLManager->setUniform3fv(blendColorUniformLocation, 1, &blendcolor[0]);

	GLsizei size = terrain->getIndexCount();
	glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_SHORT, 0);

	// Set blend color to default value
	blendcolor = vec3(1.0, 1.0, 1.0);
	mOpenGLManager->setUniform3fv(blendColorUniformLocation, 1, &blendcolor[0]);
	mOpenGLManager->bindVAO(0);
}

// Render a light source
void Renderer::renderLight(GLuint programID)
{
	vec3 ambientColor = mLightSource.getAmbientColor();
	vec3 lightPos = mLightSource.getLightPosition();
	GLuint ambientColorUniformLocation = mOpenGLManager->getUniformLocation(programID, "ambient");
	mOpenGLManager->setUniform3fv(ambientColorUniformLocation, 1, &ambientColor[0]);
	GLuint lightPositionUniformLocation = mOpenGLManager->getUniformLocation(programID, "lightpos");
	mOpenGLManager->setUniform3fv(lightPositionUniformLocation, 1, &lightPos[0]);
}

// Get the shape of the list depending of the specific shape name
Shape* Renderer::getShape(const string& shapeName)
{
	// Create list iterator to iterate over any item in the list
	vector<Shape*>::iterator it;

	// If the list is not empty
	if (mShapeList.size() > 0) {
		string shapeNameInList;
		short ret = -1;

		// Check each item in the list, if it matches the search shapeName
		for (it = mShapeList.begin(); it != mShapeList.end(); it++) {
			shapeNameInList = (*it)->getShapeName();

			ret = shapeName.compare(shapeNameInList);
			if (ret == 0)
				return (*it);	// Return the found shape
		}
	}
	return 0;
}

// Updates the rotation interval
void Renderer::updateRotInterval(GLfloat rotCube, GLfloat rotPyramid)
{
	mRotIntervalCube = rotCube;
	mRotIntervalPyramid = rotPyramid;
}

// Delete all shapes in the shape list
void Renderer::cleanup()
{
	vector<Shape*>::iterator it;

	if (mShapeList.size() > 0) {
		for (it = mShapeList.begin(); it != mShapeList.end(); ++it) {
			(*it)->cleanup();	// Clean the contents of the shape
			delete (*it);		// Delete the shape from the heap
		}
	}
}