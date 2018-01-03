#pragma once
#include "stdafx.h"

class GPUResource
{
protected:
	GLuint iResource;

	uint32_t bBound : 1;
	uint32_t iBindPoint;

	uint32_t bMapped : 1;
	uint32_t bMappable : 1;

	std::shared_ptr<void> CPUDataCopy; //CPU side copy of this iResource's data.
	uint32_t bDirty : 1; //this iResource is "dirty" when the CPU data changes, signaling that it should be re-uploaded to the GPU
public:
	GPUResource();
	~GPUResource();

	GLuint GetResource() const;

	virtual void Bind() = 0;
	virtual void Release() = 0;
};