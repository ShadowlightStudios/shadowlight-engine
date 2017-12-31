#include "stdafx.h"
#include "GPUMesh.h"


GPUMesh::GPUMesh()
{
	HasIndices = false;
	Created = false;
}


GPUMesh::~GPUMesh()
{
}

void GPUMesh::Create(const char* VertexShaderFile, const char* FragmentShaderFile, VertexData* Vertices,
	const VertexInputElement* InputElements, uint32_t NumElements, IndexData* Indices)
{
	VertexShader = std::make_unique<Shader>();
	FragmentShader = std::make_unique<Shader>();

	glGenVertexArrays(1, &iResource); //our VAO for this mesh

	if (!Vertices)
		throw std::exception("null vertex data pointer");
	else
	{
		glBindVertexArray(iResource); //start packing all of our stuff into the VAO, including vertex and index buffers and vertex input element description

		NumVertices = Vertices->NumVertices;
		VertexBuffer = std::make_unique<GPUBuffer>();
		VertexBuffer->Create(VERTEX_BUFFER, Vertices->NumVertices * Vertices->VertexStride, false, Vertices->pData);

		uint32_t BufferOffset = 0; //used to track current offset as we loop through each input element
		for (int i = 0; i < NumElements; ++i)
		{
			VertexInputElement CurrentElement = InputElements[i];
			glVertexAttribPointer(CurrentElement.Index, CurrentElement.NumElements, CurrentElement.ElementType, GL_FALSE, Vertices->VertexStride, (void*)BufferOffset);
			glEnableVertexAttribArray(i);
			BufferOffset += sizeof(float) * CurrentElement.NumElements; //advance BufferOffset by size of current element
		}

		if (Indices)
		{
			HasIndices = true;
			NumIndices = Indices->NumIndices;
			IndexBuffer = std::make_unique<GPUBuffer>();
			IndexBuffer->Create(INDEX_BUFFER, Indices->NumIndices * sizeof(uint32_t), false, Indices->pData);
		}

		Created = true;
		glBindVertexArray(0); //unbind
	}
}

void GPUMesh::Render()
{
	glUseProgram(ShaderProgram->GetResource());
	glBindVertexArray(iResource);
	
	HasIndices ? glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, 0) 
		: glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}