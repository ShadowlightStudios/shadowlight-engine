#pragma once
#include "GPUResource.h"
#include "stdafx.h"

enum GPU_BUFFER_TYPE
{
	VERTEX_BUFFER = 0,
	INDEX_BUFFER = 1,
};

class GPUBuffer : public GPUResource
{
public:
	GPUBuffer();
	~GPUBuffer();

	void Create(GPU_BUFFER_TYPE Type, uint32_t BufferSize, bool DynamicUsage = false, void* pBufferData = nullptr);

	void Update(void* pData);

	virtual void Bind() override;
	virtual void Release() override;

private:
	uint32_t GPUStorageAllocated : 1;
	uint32_t DynamicUsage : 1;

	uint32_t BufferSize; //size in bytes
};