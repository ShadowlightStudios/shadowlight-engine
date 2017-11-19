#pragma once
#include "stdafx.h"
#include "Manager.h"
#include "ShadowlightEngine.h"

class OpenGLManager: public Manager
{
private:
	const GLubyte* lpGLVersion;
	GLint iGLMajorVersion;
	GLint iGLMinorVersion;
public:
	OpenGLManager();
	~OpenGLManager();
	GLint GetOpenGLMajorVersion();
	GLint GetOpenGLMinorVersion();
};

