#include "VertexBuffer.hpp"
#include "GL.hpp"

VertexBuffer::VertexBuffer(std::initializer_list<AttribType> p_attribs, const void* p_data, unsigned int p_vertex_count) : m_vertex_count{p_vertex_count}
{
	GL::CreateVertexArrays(1, &m_vertex_array);
	GL::CreateBuffers(1, &m_vertex_buffer);

	unsigned int vertex_size = 0;
	for (AttribType attrib : p_attribs) {
		switch (attrib) {
			case Float1: vertex_size += 4;  break;
			case Float2: vertex_size += 8;  break;
			case Float3: vertex_size += 12; break;
			case Float4: vertex_size += 16; break;
		}
	}

	GL::VertexArrayVertexBuffer(m_vertex_array, 0, m_vertex_buffer, 0, vertex_size);

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

	GL::NamedBufferData(m_vertex_buffer, vertex_size * m_vertex_count, p_data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	GL::DeleteVertexArrays(1, &m_vertex_array);
	GL::DeleteBuffers(1, &m_vertex_buffer);
}

void VertexBuffer::Render()
{
	GL::BindVertexArray(m_vertex_array);
	GL::DrawArrays(GL_TRIANGLES, 0, m_vertex_count);
}
