#pragma once
#include "stdafx.h"
#include "ShaderManager.h"
#include "ShadowlightEngine.h"

// Define types of lumps
// "LT_" stands for "lump type"
#define LT_EMPTY						0x0000	
#define LT_VERTEX_SHADER				0x0001
#define LT_FRAGMENT_SHADER				0x0002
#define LT_GEOMETRY_SHADER				0x0003
#define LT_PROGRAM						0x0004
#define LT_UNIFORM						0x0005
#define LT_BUFFER						0x0006
#define LT_VERTEX_ARRAY					0x0007
#define LT_TEXTURE						0x0008
#define LT_SOUND						0x0030
#define LT_MUSIC_OGG					0x0040
#define LT_MUSIC_MP3					0x0050
#define LT_TEXT							0x0060
#define LT_INPUT_BINDINGS				0x0070
#define LT_TILE							0x0080
#define LT_TRANSFORM_FEEDBACK_BUFFER	0x0090
#define LT_FONT							0x00A0
#define LT_SCRIPT						0x00B0
#define LT_ANIMATION					0x00C0
#define LT_THING						0x00D0
#define LT_FRAMEBUFFER					0x00E0
#define LT_RENDERBUFFER					0x00F0


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

// Lump structure
struct Lump
{
	// Name
	string name;
	// Type of this lump
	uint16_t contentType;
	// Whether it's loaded or not
	bool loaded;
	// The index into whatever asset list this fits into
	int index;
	// The JSON-formatted metadata
	string metadata;
};

struct LumpNode
{
	Lump content;
	LumpNode* left;
	LumpNode* right;
};

class LumpManager
{
private:
	ShadowlightEngine *game;
public:
	void RegisterWithEngine(ShadowlightEngine* pEngine);

	LumpManager(ShadowlightEngine*);
<<<<<<< HEAD
=======
	LumpManager();
	void SetShaderManager(ShaderManager*);
>>>>>>> pr/2
	void Cleanup();
	bool LoadLump(LuaLump*);
	void LoadLumpFile(string);
	~LumpManager();
};

