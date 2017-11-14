#pragma once
#include "stdafx.h"

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

