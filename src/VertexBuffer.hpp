#pragma once
#include <initializer_list>

enum AttribType {
	Float1, Float2, Float3, Float4
};

class VertexBuffer
{
public:
	VertexBuffer(std::initializer_list<AttribType> p_attribs, const void* p_data, unsigned int p_vertex_count);
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	void Render();
private:
	unsigned int m_vertex_array;
	unsigned int m_vertex_buffer;
	unsigned int m_vertex_count;
};
