#include "stdafx.h"
#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	usable = false;
}

bool Shader::CreateShader(const char* fileName, long length, GLenum shaderType)
{
	GLchar* src;
	GLint status;
	FILE* f;

	f = fopen((const char*)fileName, "rb");
	if (!f)
	{
		RaiseError("Failed to load file %s", fileName);
		return false;
	}

	usable = false;

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
	// Setup succesful, set usable and return
	usable = true;
	return true;
}

void Shader::Cleanup()
{
	if (usable)
	{
		glDeleteShader(shaderID);
		shaderID = 0;
		usable = false;
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
