#pragma once
#include "stdafx.h"

class Shader
{
private:
	GLuint shaderID;
	bool usable;
public:
	Shader();
	~Shader();
	void Cleanup();
	bool CreateShader(const char*, long, GLenum);
	GLuint GetID();
};

