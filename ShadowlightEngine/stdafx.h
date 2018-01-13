#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;

#define SUBSYSTEM_SDL2
//#define SUBSYSTEM_GLFW

#include "GL\glew.h" //glew will be used regardless of wether SDL or GLFW is used to fire up the window and GL context
#include "Dependencies\openal\al.h"
#include "Dependencies\openal\alc.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "errors.h"
#include "lua.hpp"

#include "GPUResource.h"

#ifdef SUBSYSTEM_SDL2
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#endif