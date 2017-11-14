#include "stdafx.h"
#include "LumpManager.h"

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");

	LumpManager lm;
	string fileName;

	fileName = "C:\\Marcus\\Dropbox\\The_Way_Back\\ShadowlightEngine\\v1\\ShadowlightEngine\\Debug\\TestLump.lmp";
	
	lm.LoadLumpFile(fileName);

	lm.PrintTree();

	// Initialize GLEW
	glewInit();

	glutMainLoop();

	return 0;
}