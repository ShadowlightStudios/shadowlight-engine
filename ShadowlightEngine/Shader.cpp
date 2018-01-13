#include "stdafx.h"
#include "Shader.h"

Shader::Shader()
{
	iResource = 0;
	type = GL_NONE;
	bMappable = false;
}

// Creates a shader from the file "fileName"
// shaderType must be GL_VERTEX_SHADER, GL_FRAGMENT_SHADER,
// or GL_GEOMETRY_SHADER
bool Shader::CreateShader(const char* fileName, GLenum shaderType)
{
	// Check if this shader has already been initialized
	if (bMappable)
		return false;
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

	bMappable = false;

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

	iResource = glCreateShader(shaderType); // Create a new shader

	if (!iResource)
	{
		delete[] src;
		RaiseError("Failed to generate shader %s", fileName);
		return false;
	}

	glShaderSource(iResource, 1, &src, (const GLint*) &length);
	glCompileShader(iResource);

	// We don't need this anymore
	delete[] src;

	// Check if it compiled correctly
	glGetShaderiv(iResource, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		// Print errors, generate a buffer
		glGetShaderiv(iResource, GL_INFO_LOG_LENGTH, (GLint*) &length);
		src = new GLchar[length + 1];
		glGetShaderInfoLog(iResource, length, &status, src);
		// Cleanup
		glDeleteShader(iResource);
		printf("%s\n", src);
		RaiseError("Failed to compile shader, error log:\n%s", src);
		// We don't need this
		delete[] src;
		return false;
	}
	// Close the file
	fclose(f);
	// Setup succesful, set usable, set type, and return
	bMappable = true;
	type = shaderType;
	return true;
}

void Shader::BindToProgram(GLuint prog)
{
	glAttachShader(prog, iResource);
	// Set shader-specific
	//SetShaderSpecific(prog);
}

void Shader::Release()
{
	if (bMappable)
	{
		glDeleteShader(iResource);
		iResource = 0;
		bMappable = false;
		type = GL_NONE;
	}
}

void Shader::Bind()
{
	//do nothing
}

Shader::~Shader()
{
	Release();
}
