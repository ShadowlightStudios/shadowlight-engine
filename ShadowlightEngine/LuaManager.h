#pragma once
#include "stdafx.h"
#include "LumpManager.h"
#include "ShadowlightEngine.h"

class LuaManager
{
private:
	ShadowlightEngine* game;

	char* CStrFromString(string*);

	lua_State* L;
	int scripts;

	string currentLumpDir;
	int lumpLevel;
	int lumps;
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

