#pragma once
#include "stdafx.h"

class OpenGLManager
{
private:
	ShadowlightEngine *game;

	const GLubyte* lpGLVersion;
	GLint iGLMajorVersion;
	GLint iGLMinorVersion;
public:
	OpenGLManager(ShadowlightEngine*);
	~OpenGLManager();
	GLint GetOpenGLMajorVersion();
	GLint GetOpenGLMinorVersion();
};

