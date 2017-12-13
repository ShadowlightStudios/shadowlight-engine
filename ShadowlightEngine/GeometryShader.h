#pragma once
#include "Shader.h"
#include <list>

class GeometryShader : public Shader
{
protected:
	void SetShaderSpecific(GLuint);
	list<string> xfbVaryings;
public:
	GeometryShader();
	bool SetXFBVarying(string);
	~GeometryShader();
};

