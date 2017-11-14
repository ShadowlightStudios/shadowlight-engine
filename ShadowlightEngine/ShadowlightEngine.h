#pragma once

#include "BatchManager.h"
#include "LuaManager.h"
#include "LumpManager.h"
#include "OpenGLManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"

class ShadowlightEngine
{
public:
	ShadowlightEngine();
	~ShadowlightEngine();
	BatchManager *batchManager;
	LuaManager *luaManager;
	LumpManager *lumpManager;
	OpenGLManager *openglManager;
	ShaderManager *shaderManager;
	SoundManager *soundManager;
};

