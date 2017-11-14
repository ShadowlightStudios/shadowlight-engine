#pragma once
#include "stdafx.h"

struct DataList;
struct ElementList;

class Batch
{
private:
	int index;
	DataList* data[16];
	GLuint dataLen[16];
	bool dataUsed[16];
	ElementList* elements;
	GLuint dataBuffers[16];
	GLuint elementBuffer;
	GLuint vao;
	GLuint currentElement;
public:
	Batch();
	~Batch();
	GLuint PushData(int, GLfloat, GLfloat, GLfloat, GLfloat);
	GLuint PushElement(int);
	void Compile();
	void Bind();
	void DrawElements(GLenum, GLuint, GLuint);
};

