#include "stdafx.h"
#include "ShadowlightEngine.h"

ShadowlightEngine::ShadowlightEngine()
{
	
}

ShadowlightEngine::~ShadowlightEngine()
{
	
}

bool ShadowlightEngine::InitializeEngine(const char* AppName, int width, int height, bool fullscreen)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	WindowWidth = width;
	WindowHeight = height;
	Fullscreen = fullscreen;

	if (Fullscreen)
	{
		Window = SDL_CreateWindow(AppName, 0, 0, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		Window = SDL_CreateWindow(AppName, 0, 0, width, height, SDL_WINDOW_SHOWN);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5); //currently setting to 4.5
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	GLContext = SDL_GL_CreateContext(Window);

	if (!GLContext)
	{
		throw std::exception("unable to initialize OpenGL");
	}
	else
	{
		glewExperimental = GL_TRUE;
		GLenum glew_init = glewInit();
		if (glew_init != GLEW_OK)
		{
			throw std::exception("unable to initialize GLEW");
		}

		//Enable VSync
		SDL_GL_SetSwapInterval(1); //set to 0 to disble VSync

		return true;
	}

	return false;
}

//barebones implementation, this code (ShadowlightEngine::Run) will majorly change when we figure out more how people will be using the engine.
//this is basically just here so that we can properly run *something* to test/build on.
void ShadowlightEngine::Run()
{
	while (EngineRunning)
	{
		while (SDL_PollEvent(&SDLEvent) != 0)
		{
			if (SDLEvent.type == SDL_QUIT)
			{
				EngineRunning = false;
			}
		}

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
	SDL_GL_SwapWindow(Window);
}