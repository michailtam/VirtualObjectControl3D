/************************************************************************************/
/*																					*/
/*		File:			shapedata.h													*/
/*		Description:	This class represents the properties of the 3D vertices 	*/
/*						and the base class shape which represents the				*/
/*						shape we want to draw										*/
/*		Creation date:	15.08.2015													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once

#include "texture.h"
#include <glm\glm.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
using glm::vec3;
using glm::vec2;

// Macros
#define NUM_ARRAY_ELEMENTS(a) sizeof(a)/sizeof(*a)

const GLenum textureTarget = GL_TEXTURE_2D;


/************************************************************************************/
/*																					*/
/*		Class:			Vertex3D													*/
/*		Description:	Contains the position, normal and texture coordinate of the */
/*						Vertex														*/	
/*																					*/
/************************************************************************************/

class Vertex3D
{
public:
	// Default constructor
	Vertex3D() {}

	// Custom constructor
	Vertex3D(const vec3& position, const vec3& normal, const vec2& texCoord)
	{
		mPosition = position;
		mTextureCoord = texCoord;
		mNormal = normal;
	}

	// Getter
	vec3& getPosition() { return mPosition; }
	vec3& getNormal() { return mNormal; }
	vec2& getTexCoord() { return mTextureCoord; }

	// Setter
	void setPosition(vec3& pos) { mPosition = pos; }
	void setNormal(vec3& normal) { mNormal = normal; }
	void setTexCoord(vec2& texCoord) { mTextureCoord = texCoord; }

private:
	vec3 mPosition;		// Position of a 3D vertex [X, Y, Z]
	vec3 mNormal;		// Normal of the 3D vertex (for lightning)
	vec2 mTextureCoord;	// Texture coordinate of the 3D vertex 
};



/************************************************************************************/
/*																					*/
/*		Class:			Shape														*/
/*																					*/
/************************************************************************************/

class Shape
{
public:
	// Constructor
	Shape() :
		mShapeName(0), mpVertexArray(0), mpIndexArray(0) {}

	// Destructor
	~Shape() {}

	// Get the name of the shape
	string& getShapeName() { return (*mShapeName); }

	// Save the name of the shape
	void setShapeName(const string& shapeName)
	{
		mShapeName = new string(shapeName);
	}
	
	// ****************************** Vertex operation *******************************
	
	// Add a vertex to the vertex list 
	void addVertex(Vertex3D vertex) { mVertexList.push_back(vertex); }
	
	// The the number of vertices 
	GLint getVertexCount() { return mVertexList.size(); }

	// Get the vertices
	Vertex3D* getVertices()
	{
		if (mpVertexArray == 0) {
			mpVertexArray = new Vertex3D[mVertexList.size()];
			copy(mVertexList.begin(), mVertexList.end(), mpVertexArray);
		}
		return mpVertexArray;
	}

	// Get the buffer size of the vertices
	GLsizeiptr getVertexBufferSize()
	{
		return getVertexCount() * sizeof(Vertex3D);
	}


	// ****************************** Indices operations *****************************

	// Save the indices
	void addIndices(GLushort indices[], GLuint indexCount)
	{
		mIndexList.insert(mIndexList.begin(), indices, indices + indexCount);
	}

	// Save the indices to the list from a given vector of indices
	void setIndices(vector<GLushort> indices) { mIndexList = indices; }

	// Get the number of indices
	GLint getIndexCount() { return mIndexList.size(); }

	// Get the indices
	GLushort* getIndices()
	{
		if (mpIndexArray == 0) {
			mpIndexArray = new GLushort[mIndexList.size()];
			copy(mIndexList.begin(), mIndexList.end(), mpIndexArray);
		}
		return mpIndexArray;
	}

	// Get the buffer size of the indices
	GLsizeiptr getIndexBufferSize()
	{
		return getIndexCount() * sizeof(GLushort);
	}


	// ******************************* Texture operations ****************************
	
	// Add a texture to the texture list
	bool addTexture(const string& fileName, GLuint textureTarget, GLuint textureUnit)
	{
		// Create a texture and load the image from a file
		Texture texture(fileName, textureTarget, textureUnit);

		if (!texture.getStatus()) 
			return false;

		// Create the texture buffer 
		GLuint textureID;
		glGenTextures(1, &textureID);
		glActiveTexture(textureUnit);
		glBindTexture(textureTarget, textureID);

		// Set the filter and wrapper options of the texture and store it
		texture.setupOptions();
		texture.store();
		
		// Delete the image we have loaded from file
		texture.releaseImageData();

		mTextureMap.insert(pair<GLuint, GLuint>(textureUnit, textureID));
		glBindTexture(textureTarget, 0);	// Unbind the current bound texture

		return true;
	}

	// Bind the specific texture unit
	void bindTexture(GLuint textureUnit)
	{
		map<GLuint, GLuint>::iterator it = mTextureMap.find(textureUnit);
		if (it != mTextureMap.end()) {
			glActiveTexture(textureUnit);
			glBindTexture(GL_TEXTURE_2D, it->second);
		}
	}

	// ******************************* Surface operations ****************************



	// *************************** General shape options *****************************

	// Release the reserved memory (and on GPU) and clear all lists
	void cleanup()
	{
		delete mShapeName;
		delete[] mpVertexArray;
		delete[] mpIndexArray;

		mVertexList.clear();
		mIndexList.clear();

		// Release textures in map
		if (mTextureMap.size() > 0) {
			map<GLuint, GLuint>::iterator it;
			for (it = mTextureMap.begin(); it != mTextureMap.end(); it++) {
				glBindTexture(GL_TEXTURE_2D, it->second);
				glDeleteTextures(1, &it->second);
			}
		}
		mTextureMap.clear();
	}


protected:
	string* mShapeName;					// Name of the shape

private:
	vector<Vertex3D> mVertexList;		// Contains the properties of each vertex
	vector<GLushort> mIndexList;		// Contains the indices
	map<GLuint, GLuint> mTextureMap;	// Contains all textures (used in addition for multi-texturing)
	Vertex3D* mpVertexArray;			// Array containing the vertices
	GLushort* mpIndexArray;				// Array containing the indices
};
