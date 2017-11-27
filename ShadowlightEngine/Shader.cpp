#include "stdafx.h"
#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	type = GL_NONE;
	usable = false;
}

// Assigns an attribute to a vertex shader
// Returns false if out-of-bounds
bool Shader::SetShaderAttribute(const char* attName, int index)
{
	// Bounds checking
	if (index < 0 || index >= 16)
		return false;
	vAttributes[index] = (string)attName;
	return true;
}

// Creates a shader from the file "fileName"
// shaderType must be GL_VERTEX_SHADER, GL_FRAGMENT_SHADER,
// or GL_GEOMETRY_SHADER
bool Shader::CreateShader(const char* fileName, GLenum shaderType)
{
	GLchar* src;
	GLint status;
	long length;
	FILE* f;

	f = fopen((const char*)fileName, "rb");
	if (!f)
	{
		RaiseError("Failed to load file %s", fileName);
		return false;
	}

	usable = false;

	// Get the length
	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);

	src = new GLchar[length+1];
	if (!src)
	{
		RaiseError("Failed to allocate memory for shader %s", fileName);
		return false;
	}

	fread((void*)src, sizeof(GLchar), length, f);
	src[length] = '\0';

	shaderID = glCreateShader(shaderType); // Create a new shader

	if (!shaderID)
	{
		delete[] src;
		RaiseError("Failed to generate shader %s", fileName);
		return false;
	}

	glShaderSource(shaderID, 1, &src, (const GLint*) &length);
	glCompileShader(shaderID);

	// We don't need this anymore
	delete[] src;

	// Check if it compiled correctly
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		// Print errors, generate a buffer
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, (GLint*) &length);
		src = new GLchar[length + 1];
		glGetShaderInfoLog(shaderID, length, &status, src);
		// Cleanup
		glDeleteShader(shaderID);
		printf("%s\n", src);
		RaiseError("Failed to compile shader, error log:\n%s", src);
		// We don't need this
		delete[] src;
		return false;
	}
	// Close the file
	fclose(f);
	// Setup succesful, set usable, set type, and return
	usable = true;
	type = shaderType;
	return true;
}

void Shader::Cleanup()
{
	if (usable)
	{
		glDeleteShader(shaderID);
		shaderID = 0;
		usable = false;
		type = GL_NONE;
	}
}

GLuint Shader::GetID()
{
	if (usable)
	{
		return shaderID;
	}
	else
	{
		return 0;
	}
}


Shader::~Shader()
{
	Cleanup();
}
