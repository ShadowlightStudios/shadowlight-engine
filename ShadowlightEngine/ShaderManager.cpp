#include "stdafx.h"
#include "ShaderManager.h"
#include "ShadowlightEngine.h"


ShaderManager::ShaderManager(ShadowlightEngine* gamePointer)
{
	game = gamePointer;

	shaders = 0;
	programs = 0;
	shaderCount = 0;
	programCount = 0;
}

int ShaderManager::CreateShader()
{
	if (shaderCount != 0)
	{
		Shader **newList;
		int i;
		// If there is at least one shader,
		// Copy all of them into the new array
		shaderCount++;
		newList = new Shader*[shaderCount];
		for (i = 0; i < shaderCount-1; i++)
		{
			newList[i] = shaders[i];
		}
		// Make a new shader
		newList[i] = new Shader();
		// Delete the old pointer array
		delete[] shaders;
		// Copy the new one
		shaders = newList;
		// Then return the new index
		return shaderCount - 1;
	}
	else
	{
		// But if we don't have any shaders, just allocate one and exit
		shaders = new Shader*;
		*shaders = new Shader();
		shaderCount = 1;
		return 0;
	}
}

void ShaderManager::Cleanup()
{
	int i;
	// Delete the shaders
	if (shaders != 0)
	{
		for (i = 0; i < shaderCount; i++)
		{
			// Free this shader
			delete shaders[i];
		}
		// Then free the pointer array
		delete[] shaders;
		// Reset
		shaders = 0;
		shaderCount = 0;
	}
	// Delete the programs
	if (shaders != 0)
	{
		for (i = 0; i < programCount; i++)
		{
			// Free this program
			delete programs[i];
		}
		// Then free the pointer array
		delete[] programs;
		// Reset
		programs = 0;
		programCount = 0;
	}
}

ShaderManager::~ShaderManager()
{
	Cleanup();
}
