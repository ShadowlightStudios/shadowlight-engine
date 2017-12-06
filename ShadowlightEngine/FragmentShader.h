#pragma once
#include "Shader.h"
#include <map>

class FragmentShader : public Shader
{
private:
	void SetShaderSpecific(GLuint);
	map<int, string> colorAttachments;
public:
	FragmentShader();
	bool SetColorAttachment(string, int);
	~FragmentShader();
};

