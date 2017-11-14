#pragma once
#include "stdafx.h"
#include "ShadowlightEngine.h"

class SoundManager
{
private:
	ShadowlightEngine* game;

	ALCdevice* deviceAL;
	ALCcontext* contextAL;
public:
	SoundManager(ShadowlightEngine*);
	~SoundManager();
};

