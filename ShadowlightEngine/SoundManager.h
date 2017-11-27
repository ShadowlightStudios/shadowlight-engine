#pragma once
#include "Manager.h"

class SoundManager: public Manager
{
private:
	ALCdevice* deviceAL;
	ALCcontext* contextAL;
public:
	SoundManager();
	~SoundManager();
};

