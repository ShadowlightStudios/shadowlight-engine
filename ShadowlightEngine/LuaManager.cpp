#include "stdafx.h"
#include "LuaManager.h"

LuaManager::LuaManager(ShadowlightEngine* gamePointer)
{
	game = gamePointer;

	// Start without loading any lumps
	lumpLevel = -1;

	// Initialize lua
	L = lua_open();

	// Load libs
	luaL_openlibs(L);

	// Generate an index in the registry for the script table
	scripts = luaL_ref(L, LUA_REGISTRYINDEX);

	// Make it a table
	lua_newtable(L);
	lua_rawseti(L, LUA_REGISTRYINDEX, scripts);
}

// This function adds a script with name 'scriptName'
// into the script table
void LuaManager::AddScript(const char* scriptName, const char* contents)
{
	// First, grab the table we're writing to
	lua_rawgeti(L, LUA_REGISTRYINDEX, scripts);

	// Push the script name
	lua_pushstring(L, scriptName);

	// Push the compiled chunk that's made from contents
	luaL_loadstring(L, contents);

	// Write to the table
	lua_settable(L, -3);

	// Finally, pop the script table from the stack
	lua_pop(L, 1);
}

// Begin a lump load
void LuaManager::StartLumpLoad()
{
	// Cleanup the last load just in case ;)
	EndLumpLoad();
	currentLumpDir = "";
	// Signal to the rest of the class that we're loading
	lumpLevel = 0;
}

void LuaManager::PushLump(Lump* newLump)
{
	LuaLump* newLuaLump = (LuaLump*) lua_newuserdata(L, sizeof(LuaLump));
	newLuaLump->index = newLump->index;
	newLuaLump->contentType = newLump->contentType;
	newLuaLump->loaded = newLump->loaded;

	// Add to the current directory
	if (currentLumpDir != "")currentLumpDir += "/";
	currentLumpDir += newLump->name;

	newLuaLump->name = CStrFromString(&(newLump->name));
	newLuaLump->contentDir = CStrFromString(&currentLumpDir);
	newLuaLump->metadata = CStrFromString(&(newLump->metadata));
}

// End the lump load
void LuaManager::EndLumpLoad()
{
	// Pop all of the tables, just in case we're still in a deeper level
	while(lumpLevel > 0)
		PopLump();
	
	// Signal the end of the load
	lumpLevel = -1;
}

// Creates a new dynamically allocated C string from a C++ string
// It needs to be deleted when done with
char* LuaManager::CStrFromString(string* in)
{
	char* ret = new char[in->length() + 1];
	ret[in->length()] = '\0';
	for (unsigned int i = 0; i < in->length(); i++)
		ret[i] = (*in)[i];
	return ret;
}

// This function actually runs the script
// The script is stored in a Lua function, which
// this function executes, defining whatever
// code is inside the script
void LuaManager::LoadScript(const char* scriptName)
{
	// First, grab the table
	lua_rawgeti(L, LUA_REGISTRYINDEX, scripts);

	// Push the script name
	lua_pushstring(L, scriptName);

	// Get the script
	lua_gettable(L, -2);

	// IMPORTANT
	// Check that the script actually exists
	// If the script 'scriptName' doesn't actually exist,
	// lua_gettable will return a nil value
	// Trying to call a nil will raise an error, crashing the engine
	// Just for safety, check that it is a function,
	// not that it isn't a nil
	int type = lua_type(L, -1);

	if (type != LUA_TFUNCTION)
	{
		RaiseError(SCRIPT_NONEXISTENT);
		return;
	}

	// Now that we're past that,
	// define the script
	// by calling it
	lua_call(L, 0, 0);

	// Pop the script table
	lua_pop(L, 1);
}

LuaManager::~LuaManager()
{
	// Delete the script table in the registry
	luaL_unref(L, LUA_REGISTRYINDEX, scripts);

	// Cleanup
	lua_close(L);
}
