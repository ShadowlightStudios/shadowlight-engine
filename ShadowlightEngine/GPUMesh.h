#pragma once
#include "GPUResource.h"
#include "GPUBuffer.h"
#include "stdafx.h"

struct VertexData
{
	void* pData;
	uint32_t VertexStride; //size in bytes of one vertex including all elements
	uint32_t NumVertices;

	VertexData(void* data, uint32_t stride, uint32_t num_vertices)
	{
		pData = data;
		VertexStride = stride;
		NumVertices = num_vertices;
	}
};

struct IndexData
{
	void* pData;
	uint32_t NumIndices;

	IndexData(void* data, uint32_t num_indices)
	{
		pData = data;
		NumIndices = num_indices;
	}
};


// VertexInputElement is a CRITICAL part of our rendering code.
struct VertexInputElement
{
	uint32_t Index;         //index of this input element
	uint32_t NumElements;   //number of elements total in this input element, for example a vec3 for vertex position would result in NumElements being 3, one for each float in the vec3
	uint32_t ElementType;   //the type of each element, following the above example of a vec3, the vec3 is made of floats so GL_FLOAT would be assigned to ElementType 
	uint32_t ElementOffset; //the offset to the start of this element, for example if the vec3 for vertex position is the first element in the vertex, the offset is 0
};
//ElementOffset -- alternate example: if the element is a vec3 and it comes after a vec3 then it's offset is  (sizeof(float) * 3)

#pragma region Important Documentation
/*
EXAMPLE: this example shows the array of vertex elements to describe this vertex structure

struct Vertex
{
	vec3 Position; //vertex position
	vec3 Color;    //per vertex color
}

VertexInputElement InputElements[2]; //2 elements in each vertex, Position and Color

InputElements[0].Index = 0; //first element in the vertex
InputElements[0].NumElements = 3; //3 floats in the vec3
InputElements[0].ElementType = GL_FLOAT; //3 floats in the vec3
InputElements[0].ElementOffset = 0; //this is the first element in each vertex

InputElements[1].Index = 1;
InputElements[1].NumElements = 3;
InputElements[1].ElementType = GL_FLOAT;
InputElements[1].ElementOffset = sizeof(float) * 3; //this is the second element in each vertex and it appears after the first element of 3 floats, so it's offset is 3 floats into the buffer (12 bytes)

https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml 
*/
#pragma endregion

class GPUMesh : public GPUResource
{
public:
	GPUMesh();
	~GPUMesh();

	void Create(const char* VertexShader, const char* FragmentShader, VertexData* Vertices,
		const VertexInputElement* InputElements,uint32_t NumElements, IndexData* Indices = nullptr);

	void Render();
private:
	uint32_t Created : 1;
	uint32_t HasIndices : 1;

	uint32_t NumIndices;
	uint32_t NumVertices;

	std::unique_ptr<GPUBuffer> VertexBuffer;
	std::unique_ptr<GPUBuffer> IndexBuffer;

	std::unique_ptr<Shader> VertexShader;
	std::unique_ptr<Shader> FragmentShader;
	std::unique_ptr<Program> ShaderProgram;
};