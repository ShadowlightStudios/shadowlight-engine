#pragma once
#include "stdafx.h"
#include "ShadowlightEngine.h"

class SoundManager
{
private:
	ALCdevice* deviceAL;
	ALCcontext* contextAL;
public:
	SoundManager();
	~SoundManager();
};

