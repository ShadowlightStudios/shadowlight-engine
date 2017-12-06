#include "stdafx.h"
#include "FragmentShader.h"


// Set up the shader-specific
// We're just using a map, no need to initialize
FragmentShader::FragmentShader()
{
}

bool FragmentShader::SetColorAttachment(string name, int index)
{
	// Bounds checking
	if (index < 0)
		return false;
	// Otherwise, set the color attachment
	colorAttachments.insert(make_pair(index,name));
	return true;
}

void FragmentShader::SetShaderSpecific(GLuint prog)
{
	map<int, string>::iterator i;
	// Let's set the color attachments
	for (i = colorAttachments.begin(); i != colorAttachments.end(); ++i)
	{
		// Bind the data location
		glBindFragDataLocation(prog, i->first, i->second.data());
	}
}

// Do nothing, the base class will exit for us
FragmentShader::~FragmentShader()
{
}
