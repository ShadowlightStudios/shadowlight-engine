#pragma once
#include "stdafx.h"
#include "Shader.h" 

class Program : public GPUResource
{
public:
	Program();
	~Program();

	void CreateProgram();
	void Bind();
	void Release();
	void Link(Shader&);
	void Clean();
};