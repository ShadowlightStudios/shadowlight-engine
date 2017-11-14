#pragma once
#include "stdafx.h"
#include "Shader.h"
#include "Program.h"

class ShadowlightEngine;

class ShaderManager
{
private:
	ShadowlightEngine *game;

	Shader **shaders;
	Program **programs;
	GLuint currentProg;
	int shaderCount;
	int programCount;
public:
	ShaderManager(ShadowlightEngine*);
	int CreateShader();
	int CreateProgram();
	void Cleanup();
	~ShaderManager();
};

