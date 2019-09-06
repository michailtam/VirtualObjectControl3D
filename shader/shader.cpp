#include "shader.h"
#include <fstream>
#include <iostream>

using namespace std;


// Constructor    
Shader::Shader(const string& fileName, GLuint shaderType)
{
	// Creates the shader object and returns its id
	mShaderId = glCreateShader(shaderType);

	// Reads the shader code of the specific file
	string shaderCode = readShaderStringFromFile(fileName).c_str();
	const GLchar* shaderSourceString[1];
	shaderSourceString[0] = shaderCode.c_str();
	
	// Replaces the source code in the shader object
	glShaderSource(mShaderId, 1, shaderSourceString, 0);
}

// Destructor
Shader::~Shader()
{
}

// Read the shader source code stored in a file
string Shader::readShaderStringFromFile(const string& fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if (file.is_open()) {

		if (!file.good()) {
			cout << "Shader file %s failed to load !!!" << fileName << endl;
			file.close();
			exit(1);
		}
		else {
			while (file.good()) {
				getline(file, line);
				output.append(line + "\n");
			}
			file.close();
			return output;
		}
	}
	else {
		cout << "Error to open the shader file " << fileName << endl;
		return 0;
	}
}

