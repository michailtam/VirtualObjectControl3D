#include "glslshadermanager.h"
#include "shader\shader.h"
#include <string>
#include <iostream>

using namespace std;


// Constructor
GLSLShaderManager::GLSLShaderManager() {}

// Destructor
GLSLShaderManager::~GLSLShaderManager()
{
	cleanup();
}

// Create shader
void GLSLShaderManager::addShader(const string& fileName, GLuint shaderType)
{
	Shader* shader = new Shader(fileName, shaderType);
	mShaderList.push_back(shader);
}


// Create the shader program
void GLSLShaderManager::createProgram(const string& programName)
{
	// Create shader program 
	GLuint programID = glCreateProgram();

	// Compile the shaders and attach them to the program
	GLuint shaderID = -1;
	vector<Shader*>::iterator it;

	for (it = mShaderList.begin(); it != mShaderList.end(); it++) {
		shaderID = (*it)->getShaderId();
		glCompileShader(shaderID);

		// Check for compile errors
		if (!verifyCompilation(shaderID)) {
			cout << "Compile error occured while compilation." << endl;
			getchar();
			exit(1);
		}

		// Attach each shader to the program
		glAttachShader(programID, shaderID);
	}

	// Link the program
	glLinkProgram(programID);

	// Add program with name to map
	mProgramMap.insert(pair<string, GLuint>(programName, programID));

	shaderID = -1;
	// We no need longer the shaders
	for (it = mShaderList.begin(); it != mShaderList.end(); it++) {
		shaderID = (*it)->getShaderId();
		glDetachShader(programID, shaderID);
		glDeleteShader(shaderID);
		delete (*it);
	}

	mShaderList.clear();
}

// Use the program with specific name
void GLSLShaderManager::useProgram(const string& programName)
{
	GLuint programID = getProgramByName(programName);
	glUseProgram(programID); 
}

// Detach the current used program
void GLSLShaderManager::detachProgram()
{
	glUseProgram(0);
}

// Get shader program ID
GLuint GLSLShaderManager::getProgramByName(const string& programName)
{
	map<string, GLuint>::iterator it;
	it = mProgramMap.find(programName);

	if (it != mProgramMap.end())
		return it->second;
	else return 0;
}

// Get all the shader programs by name
void GLSLShaderManager::getAllProgramsByName(string* list)
{
	int index = 0;
	map<string, GLuint>::iterator it;
	for (it = mProgramMap.begin(); it != mProgramMap.end(); it++) {
		list[index] = it->first;
		index++;
	}
}

// Verify if the shader was compiled without errors
bool GLSLShaderManager::verifyCompilation(GLuint shaderID)
{
	GLint compileStatus;
	GLint infoLogLength;
		
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

		// Check compilation failed
		if (compileStatus != GL_TRUE) {
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* buffer = new GLchar[infoLogLength];

			GLsizei bufferSize;
			glGetShaderInfoLog(shaderID, infoLogLength, &bufferSize, buffer);
			cout << buffer << endl;	// print error message

			delete[] buffer;

			return false;
		}
	return true;
}

// Released all reserved resources
void GLSLShaderManager::cleanup()
{	
	// Release reserved memory for the programs
	glUseProgram(0);
	map<string, GLuint>::iterator itPr;
	for (itPr = mProgramMap.begin(); itPr != mProgramMap.end(); itPr++)
		glDeleteProgram((*itPr).second);

	// Clear all the list contents
	mProgramMap.clear();
}



