/************************************************************************************/
/*																					*/
/*		File:			openglmanager.h												*/
/*		Description:	This class manages all the OpenGL operations communicating	*/
/*						with the GPU												*/
/*		Creation date:	16.08.2015													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once
#include <GL\glew.h>
#include "shape\shapedata.h"
#include "shader\glslshadermanager.h"
#include "renderwindow.h"
#include <vector>
#include <map>
#include <string>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


class OpenGLManager
{
public:
	OpenGLManager();
	~OpenGLManager();

	// Buffer operations
	GLuint createVAO(const string& name);
	void bindVAO(GLuint vaoID);
	GLuint getVAO(const string& name);
	GLuint createBuffer(GLenum target, GLsizei size, GLenum usage);
	GLuint getVBO(GLuint index);
	void bindBuffer(GLenum target, GLuint bufferID);
	void storeDataInBuffer(GLuint bufferID, GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
	
	// Setup the vertex attributes
	void setupVertexArrayAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized,
		GLsizei stride, const GLvoid* pointer);

	// Attribute operations
	GLuint getUniformLocation(GLuint programID, const string& attribute);
	void setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void setUniform1i(GLuint location, GLint v0);
	void setUniform2f(GLint location, GLfloat v0, GLfloat v1);
	void setUniform3fv(GLuint location, GLsizei count, GLfloat* value);
	
	// Model-To-World transformation
	glm::mat4 getTransformationMatrix(glm::mat4& matrix, glm::vec3& rotationAxis, float rotationAngle,
			glm::vec3& translation, glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

	void cleanup();		

private:	
	void init();

	map<string, GLuint> mVaoMap;	// Contains all the VAOs	
	vector<GLuint> mBufferList;		// Contains all the buffers
};
