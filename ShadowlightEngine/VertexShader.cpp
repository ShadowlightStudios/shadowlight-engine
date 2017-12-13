#include "stdafx.h"
#include "VertexShader.h"


VertexShader::VertexShader()
{
}

bool VertexShader::SetAttribute(string name, int index)
{
	// Bounds checking
	if (index < 0 || index >= 16)
		return false;
	// Otherwise, store the attribute
	attributes.insert(make_pair(index, name));
	return true;
}

// Virtual vertex program initializer
void VertexShader::SetShaderSpecific(GLuint prog)
{
	map<int, string>::iterator i;
	// Let's set the attributes
	for (i = attributes.begin(); i != attributes.end(); ++i)
	{
		glBindAttribLocation(prog, i->first, i->second.data());
	}
	// Call GeometryShader's shader-specific
	GeometryShader::SetShaderSpecific(prog);
}

VertexShader::~VertexShader()
{
}
