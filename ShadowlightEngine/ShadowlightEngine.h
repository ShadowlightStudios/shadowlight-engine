#pragma once
#include "Manager.h"
#include "stdafx.h"

struct ShadowlightEngine
{
	Manager *luaManager;
	Manager *lumpManager;
	Manager *openglManager;
	Manager *shaderManager;
	Manager *soundManager;
	Manager *textureManager;
};