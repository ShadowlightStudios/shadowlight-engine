#include "stdafx.h"
#include "ShadowlightEngine.h"

#include "LuaManager.h"
#include "LumpManager.h"
#include "OpenGLManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");

	ShadowlightEngine sle;
	
	sle.luaManager = (Manager*) new LuaManager();
	sle.lumpManager = (Manager*) new LumpManager();
	sle.openglManager = (Manager*) new OpenGLManager();
	sle.shaderManager = (Manager*) new ShaderManager();
	sle.soundManager = (Manager*) new SoundManager();
	sle.textureManager = (Manager*) new TextureManager();

	sle.luaManager->RegisterWithEngine(&sle);
	sle.lumpManager->RegisterWithEngine(&sle);
	sle.openglManager->RegisterWithEngine(&sle);
	sle.shaderManager->RegisterWithEngine(&sle);
	sle.soundManager->RegisterWithEngine(&sle);
	sle.textureManager->RegisterWithEngine(&sle);

	string fileName;

	fileName = "C:\\Marcus\\Dropbox\\The_Way_Back\\ShadowlightEngine\\v1\\ShadowlightEngine\\Debug\\TestLump.lmp";

	// Initialize GLEW
	glewInit();

	glutMainLoop();

	return 0;
}