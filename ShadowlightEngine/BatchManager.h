#pragma once
#include "stdafx.h"
#include "ShadowlightEngine.h"

class BatchManager
{
private:
	ShadowlightEngine* game;

public:
	BatchManager();
	BatchManager(ShadowlightEngine*);
	~BatchManager();
};

