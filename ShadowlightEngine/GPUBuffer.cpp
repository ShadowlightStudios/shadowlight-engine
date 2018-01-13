#include "stdafx.h"
#include "GPUBuffer.h"


GPUBuffer::GPUBuffer()
{
	GPUStorageAllocated = false;
}


GPUBuffer::~GPUBuffer()
{
}

void GPUBuffer::Create(GPU_BUFFER_TYPE Type, uint32_t BufferSize, bool DynamicUsage, void* pBufferData)
{
	glGenBuffers(1, &iResource);
	this->BufferSize = BufferSize;
	this->DynamicUsage = DynamicUsage;

	switch (Type)
	{
		case VERTEX_BUFFER:
		{
			iBindPoint = GL_ARRAY_BUFFER;
			glBindBuffer(iBindPoint, iResource);
			break;
		}
		case INDEX_BUFFER:
		{
			iBindPoint = GL_ELEMENT_ARRAY_BUFFER;
			glBindBuffer(iBindPoint, iResource);
			break;
		}
	}

	if (pBufferData) //if pointer to buffer data is provided we can allocate GPU buffer memory here and send it the provided buffer data
	{
		glBufferData(iBindPoint, BufferSize, pBufferData, DynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		CPUDataCopy = shared_ptr<void>(pBufferData);
		bDirty = false;

		GPUStorageAllocated = true;
	}
}

void GPUBuffer::Update(void* pData)
{
	Bind();
	if (!GPUStorageAllocated)
	{
		glBufferData(iBindPoint, BufferSize, pData, DynamicUsage ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		GPUStorageAllocated = true;
	}
	else
	{
		glBufferSubData(iBindPoint, 0, BufferSize, pData);
	}
}

void GPUBuffer::Bind()
{
	glBindBuffer(iBindPoint, iResource);
}

void GPUBuffer::Release()
{
	glDeleteBuffers(1, &iResource);
	GPUStorageAllocated = false;
}