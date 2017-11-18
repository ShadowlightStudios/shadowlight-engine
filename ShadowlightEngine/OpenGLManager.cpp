#include "stdafx.h"
#include "OpenGLManager.h"
#include "ShadowlightEngine.h"

OpenGLManager::OpenGLManager(ShadowlightEngine* gamePointer)
{
	game = gamePointer;

	GLubyte* temp;
	lpGLVersion = glGetString(GL_VERSION); // Grab OpenGL version string

	printf("%s\n",lpGLVersion); // Display

	temp = (GLubyte *) lpGLVersion; // Start scanning
	iGLMajorVersion = atoi((const char*) temp);  // Extract major version
	while (*(temp++) != '.'); // Scan past '.'
	iGLMinorVersion = atoi((const char*) temp); // Extract minor version,
	printf("OpenGL version %d.%d\n", iGLMajorVersion, iGLMinorVersion); // and display.

	// One-time GL setup
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glDisableClientState(GL_NORMAL_ARRAY);
}


OpenGLManager::~OpenGLManager()
{
}
