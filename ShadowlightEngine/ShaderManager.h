#pragma once
#include "stdafx.h"
#include "Shader.h"
#include "Program.h"
#include "ShadowlightEngine.h"

class ShaderManager
{
private:
	Shader **shaders;
	Program **programs;
	GLuint currentProg;
	int shaderCount;
	int programCount;
public:
	ShaderManager();
	int CreateShader();
	int CreateProgram();
	void Cleanup();
	~ShaderManager();
};

