#pragma once
#include <list>
#include "Shader.h"

class VertexShader : public Shader
{
private:
	void SetShaderSpecific(GLuint);
	map<int, string> attributes;
	list<string> xfbVaryings;
public:
	VertexShader();
	bool SetAttribute(string, int);
	bool SetXFBVarying(string);
	~VertexShader();
};

