#pragma once
#include "stdafx.h"
#include "ShadowlightEngine.h"

class ShadowlightEngine;

class TextureManager
{
private:
	ShadowlightEngine *game;

public:
	TextureManager(ShadowlightEngine*);
	~TextureManager();
};

