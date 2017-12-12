#pragma once
#include "stdafx.h"

class Texture : public GPUResource
{
private:
	GLuint width;
	GLuint height;
	GLuint TextureFormat;

public:
	Texture(const char*);
	Texture(int width, int height, GLuint format);
	~Texture();


	GLuint GetID() const;
	GLuint GetWidth() const;
	GLuint GetHeight() const;

	void Bind();

	virtual void Release() override;
};