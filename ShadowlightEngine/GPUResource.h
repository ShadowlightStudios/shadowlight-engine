#pragma once
#include <memory>
class GPUResource
{
protected:
	GLuint iResource;

	bool bBound;
	uint32_t iBindPoint;

	bool bMapped;
	bool bMappable;

	std::shared_ptr<void> pCPUDataCopy; //CPU side copy of this iResource's data.
	bool bDirty; //this iResource is "dirty" when the CPU data changes, signaling that it should be re-uploaded to the GPU

public:
	GPUResource();
	~GPUResource();

	virtual void Bind() = 0;
	virtual void Release() = 0;

	GLuint GetResource() const;
};