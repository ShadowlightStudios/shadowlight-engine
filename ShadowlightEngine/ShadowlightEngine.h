#pragma once
#include "stdafx.h"

class ShadowlightEngine
{
public:
	ShadowlightEngine();
	~ShadowlightEngine();

	bool InitializeEngine(const char* AppName, int width, int height, bool fullscreen = false);

	void Run();
private:
	uint32_t WindowWidth;
	uint32_t WindowHeight;
	uint32_t Fullscreen : 1;
	uint32_t EngineRunning : 1;

	void BeginFrame();
	void EndFrame();


	bool InitializeGLEW();

#ifdef SUBSYSTEM_SDL2
	bool InitializeGraphicsSDL(const char* Name, int width, int height, bool fullscreen);

	SDL_Event SDLEvent;
	SDL_Window* Window;
	SDL_GLContext GLContext;
#endif

#ifdef SUBSYSTEM_GLFW
	bool InitializeGraphicsGLFW(const char* Name, int width, int height, bool fullscreen);

	GLFWwindow* pGlfwWindow;
#endif
};