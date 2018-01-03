#pragma once
#include "stdafx.h"
#include <vector>

class Shader: public GPUResource
{
protected:
	GLenum type;
	//virtual void SetShaderSpecific(GLuint) = 0; temporarily disabling this to get rendering working
	//we will work this back in without it being a virtual function
public:
	Shader();
	~Shader();

	bool CreateShader(const char*, GLenum);
	void BindToProgram(GLuint);
	virtual void Release() override;

	// We don't need to ever bind a raw shader; just return in all cases
	virtual void Bind() override; //tweaked to be override of virtual functionwhy
};