#include <cstdio>
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\openal\al.h"
#include "Dependencies\openal\alc.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "errors.h"
#include "lua.hpp"

#include "LuaManager.h"
#include "LumpManager.h"
#include "OpenGLManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"