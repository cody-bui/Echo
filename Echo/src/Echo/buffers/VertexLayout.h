#pragma once

#include <EchoHeader.h>
#include <Core.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

struct VertexElement
{
	unsigned int type;
	unsigned int byte;
	unsigned int count;
	unsigned char normalized;
};

class ECHO_DLL VertexLayout
{
private:
	std::vector<VertexElement> vertexElement;
	int stride = 0;

public:
	inline int GetStride() { return stride; }
	inline std::vector<VertexElement> GetVertexElement() { return vertexElement; }

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert();
	}

	template<>
	void Push<float>(unsigned int count)
	{
		vertexElement.push_back({ GL_FLOAT, sizeof(float), count, GL_FALSE });
		stride += sizeof(float) * count;
	}

	template<>
	void Push<int>(unsigned int count)
	{
		vertexElement.push_back({ GL_INT, sizeof(int), count, GL_FALSE });
		stride += sizeof(int) * count;
	}
};