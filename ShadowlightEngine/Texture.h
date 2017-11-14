#pragma once
#include "stdafx.h"

class Texture
{
private:
	GLuint textureID;
	GLuint width;
	GLuint height;
	bool usable;
public:
	Texture(const char*);
	~Texture();
	GLuint GetID();
	GLuint GetWidth();
	GLuint GetHeight();
	void Bind();
	void Cleanup();
};

