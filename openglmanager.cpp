#include "openglmanager.h"
#include <GL\glew.h>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a)/sizeof(*a)

// Index for the primitive restart. We set the maximum value for unsigned short
const GLushort PRIMITIVE_RESTART_INDEX = 0xFFFF;


// Constructor
OpenGLManager::OpenGLManager()
{
	init();
}

// Destructor
OpenGLManager::~OpenGLManager() {}


// Initialize OpenGL
void OpenGLManager::init()
{
	// VERY IMPORTANT:	OpenGL uses the right handed coordinate system and
	//					the right hand rotation. So we have:
	//					x	->	right of the screen
	//					y	->	up of the screen
	//					z	->	to the viewer

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);

	// Enable culling (performance win)
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Enable 2D texturing
	glEnable(GL_TEXTURE_2D);

	// Enable Primitive restart
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(PRIMITIVE_RESTART_INDEX);
}

// Create a VAO and bind it
GLuint OpenGLManager::createVAO(const string& name)
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	mVaoMap.insert(pair<string, GLuint>(name, vaoID));

	return vaoID;
}

// Bind the VAO
void OpenGLManager::bindVAO(GLuint vaoID)
{
	// NOTE: if vaoID = 0 then the current VAO will be unbind
	glBindVertexArray(vaoID);
}

// Get the VAOs id name
GLuint OpenGLManager::getVAO(const string& name)
{
	map<string, GLuint>::iterator it;

	it = mVaoMap.find(name);
	if (it != mVaoMap.end())
		return it->second;
	else
		return -1;
}

// Create an empty sized VBO buffer, to store data in it
GLuint OpenGLManager::createBuffer(GLenum target, GLsizei size, GLenum usage)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(target, bufferID);
	glBufferData(target, size, 0, usage);
	mBufferList.push_back(bufferID);
	glBindBuffer(target, 0);

	return bufferID;
}

// Get the VBO id with the specific target
GLuint OpenGLManager::getVBO(GLuint index)
{
	vector<GLuint>::iterator it = std::next(mBufferList.begin(), index);
	return (*it);
}

// Bind the VBO
void OpenGLManager::bindBuffer(GLenum target, GLuint bufferID)
{
	glBindBuffer(target, bufferID);
}

// Bind the VBO with specific bufferID and store data in it
void OpenGLManager::storeDataInBuffer(GLuint bufferID, GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	glBindBuffer(target, bufferID);
	glBufferSubData(target, offset, size, data);
}

// Setup the vertex attribute pointer
void OpenGLManager::setupVertexArrayAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

// Get the uniform position 
GLuint OpenGLManager::getUniformLocation(GLuint programID, const string& attribute)
{
	return glGetUniformLocation(programID, attribute.c_str()); 
}

// Send the matrix4fv to OpenGL
void OpenGLManager::setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
	glUniformMatrix4fv(location, count, transpose, value);
}

// Send one interger value to OpenGL
void OpenGLManager::setUniform1i(GLuint location, GLint v0)
{
	glUniform1i(location, v0);
}

// Send two GLfloats to OpenGL
void OpenGLManager::setUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
	glUniform2f(location, v0, v1);
}

// Send three GLfloats to OpenGL
void OpenGLManager::setUniform3fv(GLuint location, GLsizei count, GLfloat* value)
{
	glUniform3fv(location, count, value);
}

// Model-To-World transformation with default value of the scale vector
glm::mat4 OpenGLManager::getTransformationMatrix(glm::mat4& matrix, glm::vec3& rotationAxis, float rotationAngle,
	glm::vec3& translation, glm::vec3& scale)
{
	glm::mat4 rotationMatrix, translationMatrix, fullTransformMatrix;

	// IMPORTANT:	The direction the matrices are calculatet is the following:
	//				translate * rotate * scale;		from right to left
	//				First scale, then rotate and then translate
	translationMatrix = glm::translate(matrix, translation);
	rotationMatrix = glm::rotate(translationMatrix, rotationAngle, rotationAxis);
	fullTransformMatrix = glm::scale(rotationMatrix, scale);
	
	return fullTransformMatrix;
}

// Delete all buffers
void OpenGLManager::cleanup()
{
	GLuint vaoIndex = 1;
	GLuint bufferIndex = 1;

	vector<GLuint>::iterator itList;
	map<string, GLuint>::iterator itMap;

	if (mVaoMap.size() > 0) {
		for (itMap = mVaoMap.begin(); itMap != mVaoMap.end(); ++itMap) {
			glDeleteVertexArrays(vaoIndex, &(itMap)->second);
			vaoIndex++;
		}
	}

	if (mBufferList.size() > 0) {
		for (itList = mBufferList.begin(); itList != mBufferList.end(); itList++) {
			glDeleteVertexArrays(bufferIndex, &(*itList));
			bufferIndex++;
		}
		mBufferList.empty();
	}
}
