#pragma once
#include "Manager.h"
#include "stdafx.h"

struct ShadowlightEngine
{
	LuaManager *luaManager;
	LumpManager *lumpManager;
	OpenGLManager *openglManager;
	ShaderManager *shaderManager;
	SoundManager *soundManager;
	TextureManager *textureManager;
};