#pragma once
#include "stdafx.h"

struct ShadowlightEngine;
struct Lump;

class Manager
{
protected:
	ShadowlightEngine* pEngine;
public:
	void RegisterWithEngine(ShadowlightEngine* in) { pEngine = in; };
	virtual void Cleanup();
	virtual bool DeleteItem(int);
	virtual bool Load(int);
	virtual int Create(const Lump&);
};