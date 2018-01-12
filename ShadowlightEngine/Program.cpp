#include "stdafx.h"
#include "Program.h"

Program::Program()
{
	bMappable = false;
	iResource = 0;
	return;
}

// Generate a program
void Program::CreateProgram()
{
	iResource = glCreateProgram();

	// Check for errors
	if (!iResource)
	{
		RaiseError("Failed to generate program", "");
		return;
	}

	bMappable = true;
	bDirty = true;
}

// Link a shader to the program
void Program::Link(Shader& toLink)
{
	if (bMappable)
	{
		toLink.BindToProgram(iResource);
		bDirty = true;
	}
}

// Sets up and links the shader
void Program::Clean()
{
	if (bMappable)
	{
		// If there's nothing to do, then exit
		if (!bDirty)
			return;
		glLinkProgram(iResource);

		GLint status;
		GLint length;

		// Check for errors
		glGetProgramiv(iResource, GL_LINK_STATUS, &status);
		if (!status)
		{
			GLchar *buf;

			// Get the error log
			glGetProgramiv(iResource, GL_INFO_LOG_LENGTH, &length);

			// Create a buffer
			buf = new GLchar[length + 1];
			buf[length] = '\0';

			// Get the log text
			glGetProgramInfoLog(iResource, length, &status, buf);

			// Display, cleanup, raise error, and exit
			glDeleteProgram(iResource);

			printf("%s\n", buf);

			RaiseError("Failed to link program", "");

			return;
		}

		// Otherwise, we're clean
		bDirty = false;
	}
}

// Bind a program
void Program::Bind()
{
	if (bMappable)
	{
		if (bMapped)
			return;
		glUseProgram(iResource);
		//bMapped = true;
	}
	else
	{
		RaiseError("Attempt to bind unmappable program", "");
	}
}

// Releases the program
void Program::Release()
{
	if (bMappable)
	{
		glDeleteProgram(iResource);
		iResource = 0;
		bMappable = false;
	}
}

Program::~Program()
{
	Release();
}
