#pragma once
#include "stdafx.h"
class ShadowlightEngine;

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

