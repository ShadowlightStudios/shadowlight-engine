#pragma once
#include "stdafx.h"
#include <vector>

class Shader: public GPUResource
{
protected:
	GLenum type;
	virtual void SetShaderSpecific(GLuint) = 0;
public:
	Shader();
	~Shader();
	bool CreateShader(const char*, GLenum);
	void BindToProgram(GLuint);
	void Release();
	GLuint GetID() {
		return bMappable? iResource:0;
	};

	// We don't need to ever bind a raw shader; just return in all cases
	void Bind() { return; };
	void BindIndexed(int) { return; };
};