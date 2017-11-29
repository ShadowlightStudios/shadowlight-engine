#pragma once
#include "Manager.h"
#include "Lump.h"

class LumpManager
{
private:
	ShadowlightEngine* pEngine;
	map<string, Lump> lumps;
public:
	void RegisterWithEngine(ShadowlightEngine* pEngine) {
		this->pEngine = pEngine;
	};

	void Cleanup();
	bool EnterLump(const Lump&);
	void LoadLumpFile(string);
	Manager* ManagerFromLumpType(const Lump&);
	~LumpManager();
};