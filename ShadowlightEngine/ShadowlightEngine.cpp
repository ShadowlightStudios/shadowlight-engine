#include "stdafx.h"
#include "ShadowlightEngine.h"

#include "LuaManager.h"
#include "LumpManager.h"
#include "OpenGLManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

ShadowlightEngine::ShadowlightEngine()
{
	luaManager = new LuaManager();
	lumpManager = new LumpManager();
	openglManager = new OpenGLManager();
	shaderManager = new ShaderManager();
	soundManager = new SoundManager();
	textureManager = new TextureManager();

	luaManager->RegisterWithEngine(this);
	lumpManager->RegisterWithEngine(this);
	openglManager->RegisterWithEngine(this);
	shaderManager->RegisterWithEngine(this);
	soundManager->RegisterWithEngine(this);
	textureManager->RegisterWithEngine(this);
}

ShadowlightEngine::~ShadowlightEngine()
{
	delete luaManager;
	delete lumpManager;
	delete openglManager;
	delete shaderManager;
	delete soundManager;
	delete textureManager;
}

Lump* lProgram;
ShadowlightEngine* sle;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");

	// Initialize GLEW
	glewInit();

	string fileName;

	sle = new ShadowlightEngine;

	fileName = "..\\Debug\\TestLump.lmp";
	sle->lumpManager->LoadLumpFile(fileName);

	lProgram = sle->lumpManager->FindLump("testProg");
	sle->lumpManager->LoadLump(*lProgram);
	cout << lProgram->index << endl;

	glutMainLoop();

	delete sle;

	return 0;
}