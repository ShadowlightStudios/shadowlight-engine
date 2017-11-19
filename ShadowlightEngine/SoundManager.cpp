#include "stdafx.h"
#include "SoundManager.h"
#include "ShadowlightEngine.h"

SoundManager::SoundManager()
{
	alGetError();
	deviceAL = alcOpenDevice(NULL);
	if (deviceAL == NULL)
	{
		printf("Failed to init OpenAL device.");
		return;
	}
	contextAL = alcCreateContext(deviceAL, NULL);
	alcMakeContextCurrent(contextAL);
}


SoundManager::~SoundManager()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(contextAL);
	alcCloseDevice(deviceAL);
}
