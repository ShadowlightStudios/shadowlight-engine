#pragma once
#include "stdafx.h"

class Shader
{
private:
	GLuint shaderID;
	GLenum type;
	bool usable;
	vector<string> vAttributes;
public:
	Shader();
	~Shader();
	void Cleanup();
	bool CreateShader(const char*, GLenum);
	bool SetShaderAttribute(const char*, int);
	GLuint GetID();
};

