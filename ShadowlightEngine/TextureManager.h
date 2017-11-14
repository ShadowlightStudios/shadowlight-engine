#pragma once
#include "stdafx.h"
#include "ShadowlightEngine.h"

class TextureManager
{
private:
	ShadowlightEngine *game;

public:
	TextureManager(ShadowlightEngine*);
	~TextureManager();
};

