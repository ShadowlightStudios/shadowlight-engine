#include "stdafx.h"
#include "LuaManager.h"
#include "ShadowlightEngine.h"

// Garbage collector for LuaLump
int LuaLumpGC(lua_State* L)
{
	LuaLump* gc = (LuaLump*) lua_touserdata(L, 1);
	if (gc == NULL)
	{
		RaiseError("Tried to collect a non-lump", "");
	}

	// Return the number of returned variables
	// 0 in this case
	return 0;
}

LuaManager::LuaManager()
{
	// Start without loading any lumps
	lumpLevel = -1;

	// Initialize lua
	L = lua_open();

	// Load libs
	luaL_openlibs(L);

	// Make it a table
	lua_newtable(L);

	// Generate an index in the registry for the script table
	// This also write the table to the new registry index
	scripts = luaL_ref(L, LUA_REGISTRYINDEX);

	// Make it a table
	lua_newtable(L);

	// Generate an index in the registry for the lump table
	// This also writes the table to the new registry index
	lumps = luaL_ref(L, LUA_REGISTRYINDEX);
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

	// Begin the load by fetching the lump table
	lua_rawgeti(L, LUA_REGISTRYINDEX, scripts);
}

void LuaManager::PushLump(Lump* newLump)
{
	// If we're not loading lumps, exit
	if (lumpLevel < 0)
		return;

	// Start by generating the lump userdata
	LuaLump* newLuaLump = (LuaLump*) lua_newuserdata(L, sizeof(LuaLump));
	newLuaLump->index = newLump->index;
	newLuaLump->contentType = newLump->contentType;
	newLuaLump->loaded = newLump->loaded;
	// Add to the current directory
	if (lumpLevel != 0)currentLumpDir += "/";
	currentLumpDir += newLump->name;
	newLuaLump->name = CStrFromString(&(newLump->name));
	newLuaLump->contentDir = CStrFromString(&currentLumpDir);
	newLuaLump->metadata = CStrFromString(&(newLump->metadata));

	// parentlump lump

	// Add the name so we don't need to keep track
	lua_pushstring(L, newLuaLump->name);

	// parentlump lump name

	// Swap the lump and the name so we can use the name as the key later
	lua_insert(L, -2);

	// parentlump name lump

	// Start this lump's metatable
	lua_newtable(L);

	// parentlump name lump metatable

	// Add a garbage collector
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, LuaLumpGC);
	lua_settable(L, -3);

	// parentlump name lump metatable(with garbage)

	// Push '__index' and the table
	lua_pushstring(L, "__index");
	lua_newtable(L);

	// parentlump name lump metatable(with garbage) '__index' {}

	// Increment the lump level; we're one level deeper
	lumpLevel++;
}

void LuaManager::PopLump()
{
	// If we're not loading lumps, exit
	if (lumpLevel < 0)
		return;

	// parentlump name lump metatable(with garbage) '__index' {lumps}

	// Set the __index table to the metatable
	lua_settable(L, -3);

	// parentlump name lump metatable(with garbage and sublumps)

	// Set the metatable
	lua_setmetatable(L, -3);

	// parentlump name lump(with garbage and sublumps)

	// Write the new lump to the parent lump
	lua_settable(L, -3);

	// parentlump(with new lump)

	// Decrement the lump level, we're one level higher
	lumpLevel--;
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
		RaiseError("Script %s does not exist", scriptName);
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
