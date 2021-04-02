#include "VertexBuffer.hpp"
#include "GL.hpp"

VertexBuffer::VertexBuffer(std::initializer_list<AttribType> p_attribs, const void* p_data, unsigned int p_vertex_count) : m_vertex_count{p_vertex_count}
{
	GL::CreateVertexArrays(1, &m_vertex_array);
	GL::CreateBuffers(1, &m_vertex_buffer);

	m_vertex_size = 0;
	for (AttribType attrib : p_attribs) {
		switch (attrib) {
			case Float1: m_vertex_size += 4;  break;
			case Float2: m_vertex_size += 8;  break;
			case Float3: m_vertex_size += 12; break;
			case Float4: m_vertex_size += 16; break;
		}
	}

	GL::VertexArrayVertexBuffer(m_vertex_array, 0, m_vertex_buffer, 0, m_vertex_size);

	unsigned int offset = 0;
	unsigned int index = 0;
	for (AttribType attrib : p_attribs) {
		GL::EnableVertexArrayAttrib(m_vertex_array, index);
		switch (attrib) {
			case Float1:
				GL::VertexArrayAttribBinding(m_vertex_array, index, 0);
				GL::VertexArrayAttribFormat(m_vertex_array, index, 1, GL_FLOAT, GL_FALSE, offset);
				offset += 4;
				break;
			case Float2:
				GL::VertexArrayAttribBinding(m_vertex_array, index, 0);
				GL::VertexArrayAttribFormat(m_vertex_array, index, 2, GL_FLOAT, GL_FALSE, offset);
				offset += 8;
				break;
			case Float3:
				GL::VertexArrayAttribBinding(m_vertex_array, index, 0);
				GL::VertexArrayAttribFormat(m_vertex_array, index, 3, GL_FLOAT, GL_FALSE, offset);
				offset += 12;
				break;
			case Float4:
				GL::VertexArrayAttribBinding(m_vertex_array, index, 0);
				GL::VertexArrayAttribFormat(m_vertex_array, index, 4, GL_FLOAT, GL_FALSE, offset);
				offset += 16;
				break;
		}
		index++;
	}

	if (m_vertex_count > 0) GL::NamedBufferData(m_vertex_buffer, m_vertex_size * m_vertex_count, p_data, GL_STATIC_DRAW);
	m_vertex_count_capacity = m_vertex_count;
}

VertexBuffer::~VertexBuffer()
{
	GL::DeleteVertexArrays(1, &m_vertex_array);
	GL::DeleteBuffers(1, &m_vertex_buffer);
}

void VertexBuffer::UpdateVertices(const void* p_data, unsigned int p_vertex_count)
{
	m_vertex_count = p_vertex_count;
	if (m_vertex_count > 0 && m_vertex_count > m_vertex_count_capacity) {
		GL::NamedBufferData(m_vertex_buffer, m_vertex_size * m_vertex_count, p_data, GL_STATIC_DRAW);
		m_vertex_count_capacity = m_vertex_count;
	}
	else {
		GL::NamedBufferSubData(m_vertex_buffer, 0, m_vertex_size * m_vertex_count, p_data);
	}
}

void VertexBuffer::Clear()
{
	m_vertex_count = 0;
}

void VertexBuffer::Render()
{
	if (m_vertex_count > 0) {
		GL::BindVertexArray(m_vertex_array);
		GL::DrawArrays(GL_TRIANGLES, 0, m_vertex_count);
	}
}
