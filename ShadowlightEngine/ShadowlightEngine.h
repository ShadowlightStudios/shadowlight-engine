#pragma once
#include "stdafx.h"

class ShadowlightEngine
{
public:
	ShadowlightEngine();
	~ShadowlightEngine();

	bool InitializeEngine(const char* AppName,int width, int height, bool fullscreen = false);

	void Run();
private:
	uint32_t WindowWidth;
	uint32_t WindowHeight;
	uint32_t Fullscreen : 1;
	uint32_t EngineRunning : 1;

	SDL_Event SDLEvent;
	SDL_Window* Window;
	SDL_GLContext GLContext;

	void BeginFrame();
	void EndFrame();
};