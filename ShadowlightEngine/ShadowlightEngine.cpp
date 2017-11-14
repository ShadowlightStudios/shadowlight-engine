#include "stdafx.h"
#include "ShadowlightEngine.h"



ShadowlightEngine::ShadowlightEngine()
{
	// Create all of the managers, and link it to this class
	batchManager = new BatchManager(this);
	luaManager = new LuaManager(this);
	lumpManager = new LumpManager(this);
	openglManager = new OpenGLManager(this);
	shaderManager = new ShaderManager(this);
	soundManager = new SoundManager(this);
}


ShadowlightEngine::~ShadowlightEngine()
{
}
