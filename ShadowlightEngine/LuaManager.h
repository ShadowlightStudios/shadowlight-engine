#pragma once
#include "stdafx.h"
#include "LumpManager.h"
#include "ShadowlightEngine.h"

// A strucure made specifically for
// holding Lua userdatum lumps
struct LuaLump
{
	const char* name;
	uint16_t contentType;
	bool loaded;
	int index;
	const char* contentDir;
	const char* metadata;
};

class LuaManager
{
private:
	ShadowlightEngine* game;

	char* CStrFromString(string*);

	lua_State* L;
	int scripts;

	string currentLumpDir;
	int lumpLevel;
public:
	LuaManager(ShadowlightEngine*);
	~LuaManager();
	void AddScript(const char*, const char*);
	void LoadScript(const char* );

	void StartLumpLoad();
	void PushLump(Lump*);
	void PopLump();
	void EndLumpLoad();
};

