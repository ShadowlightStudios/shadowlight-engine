#include "stdafx.h"
#include "GPUMesh.h"
#include "Shader.h"


GPUMesh::GPUMesh()
{
	HasIndices = false;
	Created = false;
}


GPUMesh::~GPUMesh()
{
}

void GPUMesh::Create(Program* ShaderProgram, VertexData* Vertices,
	const VertexInputElement* InputElements, uint32_t NumElements, IndexData* Indices)
{
	glGenVertexArrays(1, &iResource); //our VAO for this mesh

	this->ShaderProgram = shared_ptr<Program>(ShaderProgram);

	if (!Vertices)
		throw std::exception("null vertex data pointer");
	else
	{
		glBindVertexArray(iResource); //start packing all of our stuff into the VAO, including vertex and index buffers and vertex input element description

		NumVertices = Vertices->NumVertices;
		VertexBuffer = std::make_shared<GPUBuffer>();
		VertexBuffer->Create(VERTEX_BUFFER, Vertices->NumVertices * Vertices->VertexStride, false, Vertices->pData);

		uint32_t BufferOffset = 0; //used to track current offset as we loop through each input element
		for (int i = 0; i < NumElements; ++i)
		{
			VertexInputElement CurrentElement = InputElements[i];
			glVertexAttribPointer(CurrentElement.Index, CurrentElement.NumElements, CurrentElement.ElementType, GL_FALSE, Vertices->VertexStride, (void*)BufferOffset);
			glEnableVertexAttribArray(i);
			BufferOffset += sizeof(float) * CurrentElement.NumElements; //advance BufferOffset by size of current element
			//Chances are we will not be sending in anything other than floats, if we ever do (unlikely) this will have to be modified
		}

		if (Indices)
		{
			HasIndices = true;
			NumIndices = Indices->NumIndices;
			IndexBuffer = std::make_shared<GPUBuffer>();
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