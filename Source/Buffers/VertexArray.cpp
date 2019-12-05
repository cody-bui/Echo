#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &elementID);
}

void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& vbl)
{
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement> elements = vbl.GetElement();
	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(i, elements[i].Count, elements[i].Type,
			elements[i].Normalized, vbl.GetStride(), (const void*)offset);
		offset += elements[i].Count * VertexBufferElement::GetSizeOfType(elements[i].Type);
	}
}

void VertexArray::Bind()
{
	glBindVertexArray(elementID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &elementID);
}