#include "ShadowlightEngine.h"
#include "stdafx.h"

ShadowlightEngine::ShadowlightEngine()
{
	EngineRunning = true;
}

ShadowlightEngine::~ShadowlightEngine()
{

}

bool ShadowlightEngine::InitializeEngine(const char* AppName, int width, int height, bool fullscreen)
{
#ifdef SUBSYSTEM_SDL2
	return InitializeGraphicsSDL(AppName, width, height, fullscreen);
#else
	return InitializeGraphicsGLFW(AppName, width, height, fullscreen);
#endif
}

//barebones implementation, this code (ShadowlightEngine::Run) will majorly change when we figure out more how people will be using the engine.
//this is basically just here so that we can properly run *something* to test/build on.
void ShadowlightEngine::Run()
{
	while (EngineRunning)
	{
#ifdef SUBSYSTEM_SDL2
		while (SDL_PollEvent(&SDLEvent) != 0)
		{
			if (SDLEvent.type == SDL_QUIT)
			{
				EngineRunning = false;
			}
		}
#else
		//glfw update here
#endif

		BeginFrame();
		EndFrame();
	}
}

void ShadowlightEngine::BeginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.100f, 0.149f, 0.255f, 1.0f);
}

void ShadowlightEngine::EndFrame()
{
#ifdef SUBSYSTEM_SDL2
	SDL_GL_SwapWindow(Window);
#else
	//glfw swap buffers here
#endif
}

bool ShadowlightEngine::InitializeGLEW()
{
	glewExperimental = true;

	GLenum glew_init = glewInit();
	if (glew_init != GLEW_OK)
	{
		throw std::exception("unable to initialize GLEW");
	}
	return true;
}

#ifdef SUBSYSTEM_SDL2
bool ShadowlightEngine::InitializeGraphicsSDL(const char * Name, int width, int height, bool fullscreen)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); //24 bit depth buffer

	SDL_Init(SDL_INIT_VIDEO);

	WindowWidth = width;
	WindowHeight = height;
	Fullscreen = fullscreen;

	if (Fullscreen)
	{
		Window = SDL_CreateWindow(Name, 200, 200, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
	}
	else
	{
		Window = SDL_CreateWindow(Name, 200, 200, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	}

	GLContext = SDL_GL_CreateContext(Window);

	if (!GLContext)
	{
		throw std::exception("Unable to create OpenGL context");
	}
	else
	{
		InitializeGLEW();
		SDL_GL_SetSwapInterval(1); //set to 0 to disble VSync
		return true;
	}
	return false;
}
#endif

#ifdef SUBSYSTEM_GLFW
bool ShadowlightEngine::InitializeGraphicsGLFW(const char * Name, int width, int height, bool fullscreen)
{
	return false;
}
#endif