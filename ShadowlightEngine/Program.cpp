#include "stdafx.h"
#include "Program.h"



Program::Program(GLuint vertexID, GLuint fragmentID)
{
	GLint status;
	GLint length;

	// Create a program
	programID = glCreateProgram();

	usable = false;

	// Check for errors
	if (!programID)
	{
		RaiseError(PROGRAM_CREATE_FAIL);
		return;
	}

	// Attach the vertex and fragment shaders
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);

	// And link
	glLinkProgram(programID);

	// Check for errors
	glGetProgramiv(programID, GL_LINK_STATUS, &status);
	if (!status)
	{
		GLchar *buf;
		// Get the error log
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
		// Create a buffer
		buf = new GLchar[length + 1];
		buf[length] = '\0';
		// Get the log text
		glGetProgramInfoLog(programID, length, &status, buf);
		// Display, cleanup, raise error, and exit
		glDeleteProgram(programID);
		printf("%s\n", buf);
		RaiseError(PROGRAM_LINK_FAIL);
		return;
	}

	// Find all of the uniform addresses
	m = glGetUniformLocation(programID, "mMatrix");
	v = glGetUniformLocation(programID, "vMatrix");
	p = glGetUniformLocation(programID, "pMatrix");
	mv = glGetUniformLocation(programID, "mvMatrix");
	mvp = glGetUniformLocation(programID, "mvpMatrix");
	vp = glGetUniformLocation(programID, "vpMatrix");
	c = glGetUniformLocation(programID, "colorMatrix");
	n = glGetUniformLocation(programID, "normalMatrix");
	t = glGetUniformLocation(programID, "tex");

	// Set matrices to identity
	modelMatrix = glm::mat4(1.0);
	viewMatrix = glm::mat4(1.0);
	projectionMatrix = glm::mat4(1.0);
	colorMatrix = glm::mat4(1.0);
	normalMatrix = glm::mat3(1.0);

	// Set usable and exit
	usable = true;
	return;
}

void Program::Cleanup()
{
	if (usable)
	{
		glDeleteProgram(programID);
		programID = 0;
		usable = false;
	}
}

void Program::WriteMatrices()
{
	if (usable)
	{
		// Keep a temp for combined matrices
		glm::mat4 temp;
		// Write model matrix
		if (m != -1) {
			glUniformMatrix4fv(m, 1, GL_TRUE, glm::value_ptr(modelMatrix));
		}
		// Write modelview matrix
		if (mv != -1) {
			temp = viewMatrix*modelMatrix;
			glUniformMatrix4fv(mv, 1, GL_TRUE, glm::value_ptr(temp));
		}
		// Write view matrix
		if (v != -1) {
			glUniformMatrix4fv(v, 1, GL_TRUE, glm::value_ptr(viewMatrix));
		}
		// Write viewprojection matrix
		if (vp != -1) {
			temp = projectionMatrix*viewMatrix;
			glUniformMatrix4fv(vp, 1, GL_TRUE, glm::value_ptr(temp));
		}
		// Write projection matrix
		if (p != -1) {
			glUniformMatrix4fv(p, 1, GL_TRUE, glm::value_ptr(projectionMatrix));
		}
		// Write modelviewprojection matrix
		// Calculate the mvp now; we might need it for the normal matrix
		temp = projectionMatrix*viewMatrix*modelMatrix;
		if (mvp != -1) {
			glUniformMatrix4fv(mvp, 1, GL_TRUE, glm::value_ptr(temp));
		}
		// Write color matrix
		if (c != -1) {
			glUniformMatrix4fv(vp, 1, GL_TRUE, glm::value_ptr(colorMatrix));
		}
		// Write normal matrix
		if (n != -1) {
			temp = glm::transpose(glm::inverse(glm::mat3(temp)));
			glUniformMatrix4fv(vp, 1, GL_TRUE, glm::value_ptr(temp));
		}
		// Finally, write texture
		if (t != -1)
		{
			glUniform1i(t, 0);
		}
	}
}

void Program::UseProgram()
{
	if (usable)
	{
		glUseProgram(programID);
	}
}

void Program::SetModelMatrix(glm::mat4 in)
{
	if (usable)
	{
		modelMatrix = in;
	}
}

void Program::SetViewMatrix(glm::mat4 in)
{
	if (usable)
	{
		viewMatrix = in;
	}
}

void Program::SetProjectionMatrix(glm::mat4 in)
{
	if (usable)
	{
		projectionMatrix = in;
	}
}

void Program::SetColorMatrix(glm::mat4 in)
{
	if (usable)
	{
		colorMatrix = in;
	}
}

Program::~Program()
{
	Cleanup();
}
