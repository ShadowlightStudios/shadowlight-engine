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
	Lump* FindLump(const Lump&, string) const;
	int LoadLump(Lump&);

	Manager* ManagerFromLumpType(const Lump&) const;
	~LumpManager();
};