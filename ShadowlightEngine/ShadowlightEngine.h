#pragma once
#include "Manager.h"
#include "stdafx.h"

class ShadowlightEngine
{
public:
	ShadowlightEngine();
	~ShadowlightEngine();
	LuaManager *luaManager;
	LumpManager *lumpManager;
	OpenGLManager *openglManager;
	ShaderManager *shaderManager;
	SoundManager *soundManager;
	TextureManager *textureManager;
};