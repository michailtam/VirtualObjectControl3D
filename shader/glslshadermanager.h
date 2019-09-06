/************************************************************************************/
/*																					*/
/*		File:			glslshadermanager.h											*/
/*		Description:	This class manages all the shader operations				*/
/*		Creation date:	16.08.2015													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>

using namespace std;

class Shader;


class GLSLShaderManager
{
public:
	GLSLShaderManager();
	~GLSLShaderManager();

	void addShader(const string& fileName, GLuint shaderType);
	void createProgram(const string& programName);
	void useProgram(const string& programName);
	void detachProgram();
	GLuint getProgramByName(const string& programName);
	void getAllProgramsByName(string* list);
	void cleanup();

private:
	bool verifyCompilation(GLuint shaderID);
	vector<Shader*> mShaderList;		// Temp shader list
	map<string, GLuint> mProgramMap;	// Map containing all shader programs by keyname

	
};

