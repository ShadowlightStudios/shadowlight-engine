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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");

	ShadowlightEngine sle;
	string fileName;

	fileName = "C:\\Marcus\\Dropbox\\The_Way_Back\\ShadowlightEngine\\v1\\ShadowlightEngine\\Debug\\TestLump.lmp";
	sle.lumpManager->LoadLumpFile(fileName);


	// Initialize GLEW
	glewInit();

	glutMainLoop();

	return 0;
}