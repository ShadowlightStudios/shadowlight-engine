#pragma once

// Platform dependent includes

// Windows:
#ifdef _WIN32
#include "Dependencies/lua/win32/include/lua.hpp"
// Linux:
#elif linux
#include "Dependencies/lua/linux/include/lua.hpp"
// OSX:
#elif __APPLE__
#include "Dependencies/lua/osx/include/lua.hpp"
#endif

// Needs:
// More linux versions:
// Mint
// Debian
// Ubuntu
// Redhat
// Probably more
// Windows won't be a problem
// OS X:
// I need to figure this out

// Actually, if I put it all in a Makefile, then it'll compile Lua and everything for that machine architecture/OS. 
// So I won't need to worry about this kind of thing anymore.