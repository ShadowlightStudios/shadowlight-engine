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
	bool CreateShader(FILE*, long, GLenum);
	GLuint GetID();
};

