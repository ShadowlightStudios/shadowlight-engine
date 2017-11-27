#pragma once
#include "Manager.h"
#include "Shader.h"
#include "Program.h"
#include "AssetArray.h"

class ShaderManager: public Manager
{
private:
	AssetArray<Shader> shaders;
	AssetArray<Program> programs;
	GLuint currentProg;
public:
	ShaderManager();
	int Create(const Lump&);
	void Cleanup();
	~ShaderManager();
};

