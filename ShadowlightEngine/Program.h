#pragma once
#include "stdafx.h"

class Program
{
private:
	GLuint		programID;
	glm::mat4	modelMatrix;
	glm::mat4	viewMatrix;
	glm::mat4	projectionMatrix;
	glm::mat4	colorMatrix;
	glm::mat3	normalMatrix;
	GLint		m;
	GLint		v;
	GLint		p;
	GLint		mv;
	GLint		mvp;
	GLint		vp;
	GLint		c;
	GLint		n;
	GLint		t;
	bool		usable;
public:
	Program(GLuint,GLuint);
	~Program();
	void		WriteMatrices();
	void		Cleanup();
	void		UseProgram();
	void		SetModelMatrix(glm::mat4);
	void		SetViewMatrix(glm::mat4);
	void		SetProjectionMatrix(glm::mat4);
	void		SetColorMatrix(glm::mat4);
};

