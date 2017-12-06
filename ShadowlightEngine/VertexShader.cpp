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

// Transform feedback
bool VertexShader::SetXFBVarying(string name)
{
	// Store the new transform feedback varying
	xfbVaryings.push_back(name);
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
		xfb[index] = (char*) iter->data();
	// Now, we update OpenGL
	glTransformFeedbackVaryings(prog, xfbVaryings.size(), xfb, GL_SEPARATE_ATTRIBS);
	// Alright! Now, we just delete the array we allocated, and we're done!
	delete[] xfb;
}

VertexShader::~VertexShader()
{
}
