#include "stdafx.h"
#include "ShadowlightEngine.h"

#include "LuaManager.h"
#include "LumpManager.h"
#include "OpenGLManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"

struct ShadowlightEngine
{
	LuaManager *luaManager;
	LumpManager *lumpManager;
	OpenGLManager *openglManager;
	ShaderManager *shaderManager;
	SoundManager *soundManager;
};

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");

	ShadowlightEngine sle;
	
	sle.luaManager = new LuaManager(&sle);
	sle.lumpManager = new LumpManager(&sle);
	sle.openglManager = new OpenGLManager(&sle);
	sle.shaderManager = new ShaderManager(&sle);
	sle.soundManager = new SoundManager(&sle);

	string fileName;

	fileName = "C:\\Marcus\\Dropbox\\The_Way_Back\\ShadowlightEngine\\v1\\ShadowlightEngine\\Debug\\TestLump.lmp";

	sle.lumpManager->LoadLumpFile(fileName);

	// Initialize GLEW
	glewInit();

	glutMainLoop();

	return 0;
}