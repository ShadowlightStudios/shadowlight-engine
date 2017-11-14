#pragma once
#include "stdafx.h"
#include "LumpManager.h"
#include "ShadowlightEngine.h"

class LuaManager
{
private:
	ShadowlightEngine* game;

	lua_State* L;
	int scripts;
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

