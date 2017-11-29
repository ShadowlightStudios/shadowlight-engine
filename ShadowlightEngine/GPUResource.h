#pragma once
#include <memory>

class GPUResource
{
public:
	GPUResource();
	~GPUResource();

	virtual void Release() = 0;

protected:
	uint32_t Resource;

	uint32_t Bound : 1;
	uint32_t BindPoint;

	uint32_t Mapped : 1;
	uint32_t Mappable : 1;

	std::shared_ptr<void> CPUDataCopy; //CPU side copy of this resource's data.
	uint32_t CPUDataDirty : 1; //this resource is "dirty" when the CPU data changes, signaling that it should be re-uploaded to the GPU
};