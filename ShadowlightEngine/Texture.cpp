#include "stdafx.h"
#include "Texture.h"
#include "ShadowlightEngine.h"

Texture::Texture(const char* fileName)
{
	FILE* f;
	unsigned int trash;
	long imageSize;
	int colorMode;
	unsigned char imageTypeCode;
	unsigned char bitCount;
	unsigned char *imageData;
	GLenum format;

	// First, iniatilize everything
	width = 0;
	height = 0;
	bMappable = false;


	f = fopen((const char*) fileName, "rb");
	if (!f)
	{
		RaiseError("Failed to load file %s", fileName);
		return;
	}

	// Read the two first bytes we don't need
	fread(&trash, sizeof(unsigned char), 1, f);
	fread(&trash, sizeof(unsigned char), 1, f);

	// Which type of image gets stored in imageTypeCode
	fread(&imageTypeCode, sizeof(unsigned char), 1, f);

	// For our purposes, the type code should be 2 (uncompressed RGB image)
	// or 3 (uncompressed black-and-white images).
	if (imageTypeCode != 2 && imageTypeCode != 3)
	{
		fclose(f);
		RaiseError("Targa file %s has unrecognized type", fileName);
		return;
	}

	// Read 13 bytes of data we don't need
	fread(&trash, sizeof(short int), 1, f);
	fread(&trash, sizeof(short int), 1, f);
	fread(&trash, sizeof(unsigned char), 1, f);
	fread(&trash, sizeof(short int), 1, f);
	fread(&trash, sizeof(short int), 1, f);

	// Read the image's width and height
	fread(&width, sizeof(short int), 1, f);
	fread(&height, sizeof(short int), 1, f);

	// Read the bit depth
	fread(&bitCount, sizeof(unsigned char), 1, f);

	// Read one byte of data we don't need
	fread(&trash, sizeof(unsigned char), 1, f);

	// Color mode -> 3 = BGR, 4 = BGRA
	colorMode = bitCount / 8;
	imageSize = width * height * colorMode;

	if (colorMode == 3)
	{
		format = GL_BGR;
	}
	else if (colorMode == 4)
	{
		format = GL_BGRA;
	}
	else
	{
		fclose(f);
		RaiseError("Targa files %s has unrecognized color mode", fileName);
		return;
	}

	// Allocate memory for the image data
	imageData = new unsigned char[imageSize];

	if (!imageData)
	{
		fclose(f);
		RaiseError("Failed to allocate data from image %s", fileName);
		return;
	}

	// Read the image data
	fread(imageData, sizeof(unsigned char), imageSize, f);

	// Close the file
	fclose(f);

	// Create the texture
	glGenTextures(1, &iResource);
	glBindTexture(GL_TEXTURE_2D, iResource);
	if (glIsTexture(iResource) == GL_TRUE)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	else
	{
		delete[] imageData;
		RaiseError("Failed to generate texture %s", fileName);
		return;
	}
	delete[] imageData;
	bMappable = true;
	return;
}

Texture::Texture(int width, int height, GLuint format)
{
	this->width = width;
	this->height = height;
	this->TextureFormat = format;
	bMappable = false;

	glGenTextures(1, &iResource);
	iBindPoint = GL_TEXTURE_2D;
	glBindTexture(iBindPoint, iResource);
	bBound = true;

	if (glIsTexture(iResource) == GL_TRUE)
	{
		glTexParameteri(iBindPoint, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(iBindPoint, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(iBindPoint, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(iBindPoint, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexImage2D(iBindPoint, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		//TODO: implement method for setting texture data and then calling glTexImage2D to commit data to GPU
	}
}

GLuint Texture::GetID() const
{
	return bMappable ? iResource : 0;
}

GLuint Texture::GetWidth() const
{
	return width; //no reason not to return width/height at any time to anything. for example for computations on procedural textures before fully "usable"
}

GLuint Texture::GetHeight() const
{
	return height;
}

void Texture::Bind()
{
	if (bMappable)
	{
		glBindTexture(iBindPoint, iResource);

		bBound = true;
		iBindPoint = GL_TEXTURE_2D;
	}
}

void Texture::Release()
{
	if (bMappable)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &iResource);
		iResource = 0;
		bBound = false;
		iBindPoint = 0;
	}
}


Texture::~Texture()
{
	Release();
}