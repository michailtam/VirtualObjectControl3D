/************************************************************************************/
/*																					*/
/*		File:			texture.h													*/
/*		Description:	This class manages texture operations. To load the texture	*/
/*						dtata from a file we use the SOIL library					*/
/*						http://www.lonesock.net/soil.html							*/
/*		Creation date:	03.09.2015													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <SOIL.h>
#include <string>
#include <iostream>

using namespace std;


class Texture
{
public:
	// Constructor
	Texture(const string& fileName, GLuint textureTarget, GLuint textureUnit)
	{
		// Load the image from file
		mpImage = SOIL_load_image(fileName.c_str(), &mWidthS, &mHeightT, &mChannels, SOIL_LOAD_AUTO);

		if (mpImage == 0) {
			cerr << "Error while loading texture from file" << fileName.c_str() << endl;
			mbSuccesfull = false;
		}

		// Swap the image upside down. We use the code snippet from the OpenGL Development Cookbook
		// by Muhammad Mobeen Movania
		int i, j;
		for (j = 0; j * 2 < mHeightT; ++j)
		{
			int index1 = j * mWidthS * mChannels;
			int index2 = (mHeightT - 1 - j) * mWidthS * mChannels;
			for (i = mWidthS * mChannels; i > 0; --i)
			{
				GLubyte temp = mpImage[index1];
				mpImage[index1] = mpImage[index2];
				mpImage[index2] = temp;
				++index1;
				++index2;
			}
		}

		// Save the texture target and texture unit
		mTextureTarget = textureTarget;
		mTextureUnit = textureUnit;

		mbSuccesfull = true;

		// For testing example if channels are 4 this equals to RGBA and contains 4 bytes R G B A
		// printf("The first 4 bytes are: %i, %i, %i, %i\n", mpImage[0], mpImage[1], mpImage[2], mpImage[3]);
	}

	// Destructor
	~Texture() 
	{
	}

	// Getters
	int getTextureWidthS() { return mWidthS; }
	int getTextureHeightT() { return mHeightT; }
	int getTextureChannels() { return mChannels; }
	unsigned char* getImageData() { return mpImage; }
	GLuint getTextureTarget() { return mTextureTarget; }
	GLuint getTextureUnit() { return mTextureUnit; }
	bool getStatus() { return mbSuccesfull; }

	// Delete texture
	void releaseImageData()
	{
		SOIL_free_image_data(mpImage);
	}

	// Store the 2D texture
	void store()
	{
		// Store the texture data in buffer and generate mipmap
		glTexImage2D(mTextureTarget, 0, GL_RGB, mWidthS, mHeightT, 0, GL_RGB, GL_UNSIGNED_BYTE, mpImage);
	}

	// Set the texture wrapping/filter options and create the texture from the image data
	void setupOptions()
	{
		glTexParameteri(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(mTextureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(mTextureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

private:
	unsigned char* mpImage;		// Image data
	int mWidthS;				// Width of the texture (S)
	int mHeightT;				// Height of the texture (T)
	int mChannels;				// Channels of the texture (example 4 for RGBA)
	GLuint mTextureTarget;		// Texture target (example: GL_TEXTURE_2D)
	GLuint mTextureUnit;		// Texture unit (example: GL_TEXTURE0 or GL_TEXTURE1 or ...)
	bool mbSuccesfull;			// Flag for determining if the texture was successfull loaded
};

