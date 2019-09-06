/************************************************************************************/
/*																					*/
/*		File:			shader.h													*/
/*		Description:	This class represents a shader								*/
/*		Creation date:	16.08.2015													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once

#include <string>
#include <GL\glew.h>

using namespace std;

class Shader
{
public:
	Shader(const string& fileName, GLuint shaderType);
	~Shader();

	// Getter
	GLuint getShaderId() { return mShaderId;  }

private:
	// Read shader source code from file
	string readShaderStringFromFile(const string& fileName);

	GLuint mShaderId;	// Shader ID
};

