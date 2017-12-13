#pragma once
#include <list>
#include "GeometryShader.h"

class VertexShader : public GeometryShader
{
private:
	void SetShaderSpecific(GLuint);
	map<int, string> attributes;
public:
	VertexShader();
	bool SetAttribute(string, int);
	~VertexShader();
};

