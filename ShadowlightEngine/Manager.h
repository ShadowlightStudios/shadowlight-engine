#pragma once
#include "errors.h"

class ShadowlightEngine;
class Lump;

class Manager
{
protected:
	ShadowlightEngine* pEngine;
public:
	void RegisterWithEngine(ShadowlightEngine* pEngine) { this->pEngine = pEngine; };
	virtual void Cleanup() { RaiseError("WIP", ""); }
	virtual bool DeleteItem(int) { RaiseError("WIP", ""); return false; }
	virtual int Create(const Lump&) { RaiseError("WIP", ""); return -1; }
	virtual ~Manager() {};
};