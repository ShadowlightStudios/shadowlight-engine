#pragma once

struct ShadowlightEngine;
class Lump;

class Manager
{
protected:
	ShadowlightEngine* pEngine;
public:
	void RegisterWithEngine(ShadowlightEngine* pEngine) { this->pEngine = pEngine; };
	virtual void Cleanup();
	virtual bool DeleteItem(int);
	virtual bool Load(int);
	virtual int Create(const Lump&);
};