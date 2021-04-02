#pragma once
#include <vector>
#include <queue>
#include "Renderer.hpp"

class ChunkStorage
{
public:
	ChunkStorage(unsigned int p_width, unsigned int p_height, unsigned int p_depth);
	~ChunkStorage();

	template<bool empty>
	unsigned int NewChunk();
	void DeleteChunk(unsigned int p_chunk_index);

	void GenerateChunk(unsigned int p_chunk_index);
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