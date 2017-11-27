#pragma once
#include "LumpManager.h"
#include "Manager.h"

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

class LuaManager: public Manager
{
private:
	char* CStrFromString(string*);

	lua_State* L;
	int scripts;

	string currentLumpDir;
	int lumpLevel;
	int lumps;
public:
	LuaManager();
	~LuaManager();
	void AddScript(const char*, const char*);
	void LoadScript(const char* );

	void StartLumpLoad();
	void PushLump(Lump*);
	void PopLump();
	void EndLumpLoad();
};

