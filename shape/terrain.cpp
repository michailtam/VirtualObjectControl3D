#include "terrain.h"
#include <SOIL.h>
#include <iostream>
#include <fstream>

const string HEIGHT_MAP_FILE = "./res/height_map.jpg";
const string TERRAIN_TEXTURE_FILE = "./res/terrain.jpg";
const GLushort PRIMITIVE_RESTART_INDEX = 0xFFFF;


// Constructor
Terrain::Terrain(float width, float depth, bool heightMapChoosen, 
	float maxHeight, const string& name)
{
	mWidth = width;
	mDepth = depth;
	mMaxHeight = maxHeight;

	mbHeightMapChoosen = heightMapChoosen;

	setShapeName(name);

	generateVertices();		// Generates the vertices
	generateIndices();		// Generate the indices
	//generateNormals();		// Generate the normals

	// Set texture
	addTexture(TERRAIN_TEXTURE_FILE, GL_TEXTURE_2D, GL_TEXTURE2);
}

// Destructor
Terrain::~Terrain()
{
	SOIL_free_image_data(mpImage);
}

// Generate vertices
void Terrain::generateVertices()
{
	float* buffer = 0;

	// Calculate the height map values if is choosen
	if (mbHeightMapChoosen) {
		loadHeightMap(HEIGHT_MAP_FILE);	// Load the height map

		// Calculate the amount of pixels in height map
		unsigned int maxPixels = mHeightMapDimensions.x * mHeightMapDimensions.y;
		buffer = new float[maxPixels];
		calcHeightMapValues(buffer, maxPixels);
	}

	// Calculate start position at the negative X and Z axis
	float X = float(mWidth) / (float)2;
	X *= -1;
	float Z = float(mDepth) / (float)2;
	Z *= -1;

	float startX = X;
	float startZ = Z;

	int i, j, counter = 0;
	bool isTop = true;
	vec3 position;
	vec2 texCoord = vec2(0.0f, 1.0f);
	vector<Vertex3D> tmpVertices;

	Vertex3D vertex;

	position.z = startZ;
	for (i = 0; i < mDepth; i++) {
		position.x = startX;	// Set the start position on the X axis

		for (j = 0; j < mWidth + 1; j++) {
			if (!mbHeightMapChoosen)
				vertex.setPosition(vec3(position.x, 0, position.z));
			else {
				vertex.setPosition(vec3(position.x, buffer[counter], position.z));
				counter++;
			}

			// The the normal of the vertex, all normals on the terrain are 
			// pointing upwards on the Y axis
			vertex.setNormal(vec3(0.0f, 1.0f, 0.0f));	

			// If the first texture coordinate of the depth i
			if (j > 0)
				texCoord.x = !texCoord.x;	// Toggle the x value 1 to 0 to 1 ...

			vertex.setTexCoord(texCoord);	
			tmpVertices.push_back(vertex);	// Save texture coordinate in temp list
			position.x += 1.0f;	// Add offset to next vertice on column j 
		}
		texCoord.y = !texCoord.y;	// Toggle the y value 1 to 0 to 1 ...
		position.z += 1.0f;	// Add offset to next vertice on depth i 
	}

	// Safe vertices, texture coordinates and indices
	vector<Vertex3D>::iterator it;
	for (it = tmpVertices.begin(); it != tmpVertices.end(); it++)
		addVertex(*it);

	if (!buffer)
		delete[] buffer;
}

// Calculate the heightmap values
void Terrain::calcHeightMapValues(float buffer[], unsigned int maxPixels)
{
	float heightValue;

	for (unsigned int i = 0; i < maxPixels; i++) {
		heightValue = (mMaxHeight / 255.0f) * (float)mpImage[i];
		buffer[i] = heightValue;
	}
}

// Generate the indices
void Terrain::generateIndices()
{
	// Calculate indices
	vector<GLushort> tmpIndices;
	GLuint currentIndex = 0;

	bool firstQuadOfRow = true;
	int i, j;
	for (i = 0; i < mDepth; i++) {
		for (j = 0; j < mWidth; j++) {

			// Create the indices of the first quad in row i
			if (firstQuadOfRow) {
				tmpIndices.push_back(currentIndex);
				tmpIndices.push_back(currentIndex + mWidth + 1);
				tmpIndices.push_back(currentIndex + 1);
				tmpIndices.push_back(currentIndex + mWidth + 2);
				firstQuadOfRow = false;
			} 
			else {
				tmpIndices.push_back(currentIndex + 1);
				tmpIndices.push_back(currentIndex + mWidth + 2);
			}
			currentIndex++;
		}

		// Save the triangle strip and continue on next depth
		tmpIndices.push_back(PRIMITIVE_RESTART_INDEX);
		firstQuadOfRow = true;
		currentIndex++;
	}

	// Save the indices
	setIndices(tmpIndices);
}

// Generate the normals for lightning purposes
void Terrain::generateNormals()
{

}

// Load the heightmap image 
bool Terrain::loadHeightMap(const string& fileName)
{
	int width, height, channels;

	// Load the image from file
	mpImage = SOIL_load_image(fileName.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

	if (mpImage == 0) {
		cerr << "Error while loading height map from file" << fileName.c_str() << endl;
		return false;
	}

	// Swap the image upside down. We use the code snippet from the OpenGL Development Cookbook
	// by Muhammad Mobeen Movania
	int i, j;
	for (j = 0; j * 2 < height; ++j)
	{
		int index1 = j * width * mChannels;
		int index2 = (height - 1 - j) * width * channels;
		for (i = width * mChannels; i > 0; --i)
		{
			GLubyte temp = mpImage[index1];
			mpImage[index1] = mpImage[index2];
			mpImage[index2] = temp;
			++index1;
			++index2;
		}
	}

	// Set the dimensions of the height map
	mHeightMapDimensions = vec2(width, height);

	return true;
}
