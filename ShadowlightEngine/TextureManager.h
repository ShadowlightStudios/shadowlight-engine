#pragma once
#include "stdafx.h"

class ShadowlightEngine;

class TextureManager
{
private:
	ShadowlightEngine *game;

public:
	TextureManager(ShadowlightEngine*);
	~TextureManager();
};

