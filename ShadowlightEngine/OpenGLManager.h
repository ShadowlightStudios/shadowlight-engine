#pragma once
#include "stdafx.h"
#include "ShadowlightEngine.h"

class ShadowlightEngine;

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

