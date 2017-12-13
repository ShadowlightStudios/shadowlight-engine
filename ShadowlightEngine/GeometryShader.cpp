#include "stdafx.h"
#include "GeometryShader.h"

GeometryShader::GeometryShader()
{
}

// Transform feedback
bool GeometryShader::SetXFBVarying(string name)
{
	// Store the new transform feedback varying
	xfbVaryings.push_back(name);
	return true;
}

// Shader-specific
void GeometryShader::SetShaderSpecific(GLuint prog)
{
	// Make an array to store our transform feedback varyings
	// First, make sure that we have some
	if (xfbVaryings.size() == 0)
		return;
	// If we've made it this far, then we have some varyings to initialize
	char** xfb = new char*[xfbVaryings.size()];
	// Set the datapoints
	list<string>::iterator iter;
	int index;
	for (iter = xfbVaryings.begin(), index = 0; iter != xfbVaryings.end(); ++iter, ++index)
		xfb[index] = (char*)iter->data();
	// Now, we update OpenGL
	glTransformFeedbackVaryings(prog, xfbVaryings.size(), xfb, GL_SEPARATE_ATTRIBS);
	// Alright! Now, we just delete the array we allocated, and we're done!
	delete[] xfb;
}

GeometryShader::~GeometryShader()
{
}
