#pragma once
#include <vector>
#include <queue>
#include <glm/vec3.hpp>
#include "VertexBuffer.hpp"
#include "Renderer.hpp"

class ChunkStorage
{
public:
	ChunkStorage(unsigned int p_width, unsigned int p_height, unsigned int p_depth);
	~ChunkStorage();

	// template<bool empty>
	// unsigned int NewChunk();

	template <bool empty>
	unsigned int NewChunk()
	{
		if (!m_free_chunks.empty()) {
			unsigned int index = m_free_chunks.front();
			m_free_chunks.pop();
			return index;
		}
		else {
			unsigned int index = m_chunks.size() / m_chunk_size;
			m_chunks.resize(m_chunks.size() + m_chunk_size);
			VertexBuffer* vertex_buffer = reinterpret_cast<VertexBuffer*>(m_chunks.data() + ((index + 1) * m_chunk_size) - sizeof(VertexBuffer));
			new(vertex_buffer) VertexBuffer({Float3, Byte3Norm, Float3});
			if constexpr (empty) {
				vertex_buffer->Clear();
				for (unsigned long long i = index * m_chunk_size; i < (index * m_chunk_size) + (m_width * m_height * m_depth); i++) {
					m_chunks[i] = 0;
				}
			}
			return index;
		}
	}

	void DeleteChunk(unsigned int p_chunk_index);

	void GenerateChunk(unsigned int p_chunk_index, glm::ivec3 chunk_pos);
	void GenerateMesh(unsigned int p_chunk_index);
	void Render(unsigned int p_chunk_index);
private:
	std::vector<unsigned char> m_chunks;
	std::queue<unsigned int>   m_free_chunks;

	unsigned int m_chunk_size;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_depth;
};