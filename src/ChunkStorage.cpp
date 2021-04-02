#include "ChunkStorage.hpp"
#include "VertexBuffer.hpp"
#include <new>

ChunkStorage::ChunkStorage(unsigned int p_width, unsigned int p_height, unsigned int p_depth) : m_width{p_width}, m_height{p_height}, m_depth{p_depth}
{
	m_chunk_size = (m_width * m_height * m_depth) + sizeof(VertexBuffer);
}

ChunkStorage::~ChunkStorage()
{
	for (unsigned long long i = m_chunk_size - sizeof(VertexBuffer); i < m_chunks.size(); i += m_chunk_size - sizeof(VertexBuffer)) {
		reinterpret_cast<VertexBuffer*>(m_chunks.data() + i)->~VertexBuffer();
	}
}

template <bool empty>
unsigned int ChunkStorage::NewChunk()
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

void ChunkStorage::DeleteChunk(unsigned int p_chunk_index)
{
	m_free_chunks.push(p_chunk_index);
}

void ChunkStorage::GenerateChunk(unsigned int p_chunk_index)
{
	unsigned char* voxels = m_chunks.data() + (p_chunk_index * m_chunk_size);

	auto SetVoxel = [this, voxels](unsigned int x, unsigned int y, unsigned int z, unsigned char voxel) {
		voxels[(y * m_width * m_depth) + (z * m_width) + x] = voxel;
	};

	SetVoxel(0, 0, 0, 1);
	SetVoxel(1, 0, 0, 1);
	SetVoxel(2, 0, 0, 1);
	SetVoxel(3, 0, 0, 1);
	SetVoxel(4, 0, 0, 1);
	SetVoxel(0, 1, 0, 1);
	SetVoxel(0, 2, 0, 1);
	SetVoxel(0, 0, 1, 1);
	SetVoxel(0, 0, 2, 1);
}

#pragma pack(1)
struct Vertex
{
	template<char index> static Vertex MakeLeftFace(unsigned int x, unsigned int y, unsigned int z) {
		if constexpr (index == 0) return Vertex{static_cast<float>(x),static_cast<float>(y),     static_cast<float>(z),     -1,0,0,0.0f,0.0f,0.0f};
		if constexpr (index == 1) return Vertex{static_cast<float>(x),static_cast<float>(y)+1.0f,static_cast<float>(z),     -1,0,0,1.0f,0.0f,0.0f};
		if constexpr (index == 2) return Vertex{static_cast<float>(x),static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,-1,0,0,1.0f,1.0f,0.0f};
		if constexpr (index == 3) return Vertex{static_cast<float>(x),static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,-1,0,0,1.0f,1.0f,0.0f};
		if constexpr (index == 4) return Vertex{static_cast<float>(x),static_cast<float>(y),     static_cast<float>(z)+1.0f,-1,0,0,0.0f,1.0f,0.0f};
		if constexpr (index == 5) return Vertex{static_cast<float>(x),static_cast<float>(y),     static_cast<float>(z),     -1,0,0,0.0f,0.0f,0.0f};
	}

	template<char index> static Vertex MakeRightFace(unsigned int x, unsigned int y, unsigned int z) {
		if constexpr (index == 0) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y),     static_cast<float>(z),     1,0,0,0.0f,0.0f,0.0f};
		if constexpr (index == 1) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y),     static_cast<float>(z)+1.0f,1,0,0,0.0f,1.0f,0.0f};
		if constexpr (index == 2) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,1,0,0,1.0f,1.0f,0.0f};
		if constexpr (index == 3) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,1,0,0,1.0f,1.0f,0.0f};
		if constexpr (index == 4) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z),     1,0,0,1.0f,0.0f,0.0f};
		if constexpr (index == 5) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y),     static_cast<float>(z),     1,0,0,0.0f,0.0f,0.0f};
	}

	template<char index> static Vertex MakeTopFace(unsigned int x, unsigned int y, unsigned int z) {
		if constexpr (index == 0) return Vertex{static_cast<float>(x),     static_cast<float>(y),static_cast<float>(z),     0,-1,0,0.0f,0.0f,0.0f};
		if constexpr (index == 1) return Vertex{static_cast<float>(x),     static_cast<float>(y),static_cast<float>(z)+1.0f,0,-1,0,0.0f,1.0f,0.0f};
		if constexpr (index == 2) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y),static_cast<float>(z)+1.0f,0,-1,0,1.0f,1.0f,0.0f};
		if constexpr (index == 3) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y),static_cast<float>(z)+1.0f,0,-1,0,1.0f,1.0f,0.0f};
		if constexpr (index == 4) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y),static_cast<float>(z),     0,-1,0,1.0f,0.0f,0.0f};
		if constexpr (index == 5) return Vertex{static_cast<float>(x),     static_cast<float>(y),static_cast<float>(z),     0,-1,0,0.0f,0.0f,0.0f};
	}

	template<char index> static Vertex MakeBottomFace(unsigned int x, unsigned int y, unsigned int z) {
		if constexpr (index == 0) return Vertex{static_cast<float>(x),     static_cast<float>(y)+1.0f,static_cast<float>(z),     0,1,0,0.0f,0.0f,0.0f};
		if constexpr (index == 1) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z),     0,1,0,1.0f,0.0f,0.0f};
		if constexpr (index == 2) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,0,1,0,1.0f,1.0f,0.0f};
		if constexpr (index == 3) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,0,1,0,1.0f,1.0f,0.0f};
		if constexpr (index == 4) return Vertex{static_cast<float>(x),     static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,0,1,0,0.0f,1.0f,0.0f};
		if constexpr (index == 5) return Vertex{static_cast<float>(x),     static_cast<float>(y)+1.0f,static_cast<float>(z),     0,1,0,0.0f,0.0f,0.0f};
	}

	template<char index> static Vertex MakeFrontFace(unsigned int x, unsigned int y, unsigned int z) {
		if constexpr (index == 0) return Vertex{static_cast<float>(x),     static_cast<float>(y),     static_cast<float>(z),0,0,-1,0.0f,0.0f,0.0f};
		if constexpr (index == 1) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y),     static_cast<float>(z),0,0,-1,1.0f,0.0f,0.0f};
		if constexpr (index == 2) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z),0,0,-1,1.0f,1.0f,0.0f};
		if constexpr (index == 3) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z),0,0,-1,1.0f,1.0f,0.0f};
		if constexpr (index == 4) return Vertex{static_cast<float>(x),     static_cast<float>(y)+1.0f,static_cast<float>(z),0,0,-1,0.0f,1.0f,0.0f};
		if constexpr (index == 5) return Vertex{static_cast<float>(x),     static_cast<float>(y),     static_cast<float>(z),0,0,-1,0.0f,0.0f,0.0f};
	}

	template<char index> static Vertex MakeBackFace(unsigned int x, unsigned int y, unsigned int z) {
		if constexpr (index == 0) return Vertex{static_cast<float>(x),     static_cast<float>(y),     static_cast<float>(z)+1.0f,0,0,1,0.0f,0.0f,0.0f};
		if constexpr (index == 1) return Vertex{static_cast<float>(x),     static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,0,0,1,0.0f,1.0f,0.0f};
		if constexpr (index == 2) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,0,0,1,1.0f,1.0f,0.0f};
		if constexpr (index == 3) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y)+1.0f,static_cast<float>(z)+1.0f,0,0,1,1.0f,1.0f,0.0f};
		if constexpr (index == 4) return Vertex{static_cast<float>(x)+1.0f,static_cast<float>(y),     static_cast<float>(z)+1.0f,0,0,1,1.0f,0.0f,0.0f};
		if constexpr (index == 5) return Vertex{static_cast<float>(x),     static_cast<float>(y),     static_cast<float>(z)+1.0f,0,0,1,0.0f,0.0f,0.0f};
	}

	float px, py, pz; // a_position
	char  nx, ny, nz; // a_normal
	float tx, ty, tz; // a_texture_coordinate
};
#pragma pack()

void ChunkStorage::GenerateMesh(unsigned int p_chunk_index)
{
	unsigned char* voxels = m_chunks.data() + (p_chunk_index * m_chunk_size);
	
	std::vector<Vertex> vertices;

	auto TestVoxel = [this, voxels](unsigned int x, unsigned int y, unsigned int z) -> bool {
		return voxels[(y * m_width * m_depth) + (z * m_width) + x];
	};

	for (unsigned int y = 0; y < m_height; y++) {
		for (unsigned int z = 0; z < m_depth; z++) {
			for (unsigned int x = 0; x < m_width; x++) {
				if (!TestVoxel(x, y, z)) continue;
				if (x == 0 || !TestVoxel(x - 1, y, z)) {
					// Add left face
					vertices.push_back(Vertex::MakeLeftFace<0>(x, y, z));
					vertices.push_back(Vertex::MakeLeftFace<1>(x, y, z));
					vertices.push_back(Vertex::MakeLeftFace<2>(x, y, z));
					vertices.push_back(Vertex::MakeLeftFace<3>(x, y, z));
					vertices.push_back(Vertex::MakeLeftFace<4>(x, y, z));
					vertices.push_back(Vertex::MakeLeftFace<5>(x, y, z));
				}
				if (x == m_width - 1 || !TestVoxel(x + 1, y, z)) {
					// Add right face
					vertices.push_back(Vertex::MakeRightFace<0>(x, y, z));
					vertices.push_back(Vertex::MakeRightFace<1>(x, y, z));
					vertices.push_back(Vertex::MakeRightFace<2>(x, y, z));
					vertices.push_back(Vertex::MakeRightFace<3>(x, y, z));
					vertices.push_back(Vertex::MakeRightFace<4>(x, y, z));
					vertices.push_back(Vertex::MakeRightFace<5>(x, y, z));
				}
				if (y == 0 || !TestVoxel(x, y - 1, z)) {
					// Add top face
					vertices.push_back(Vertex::MakeTopFace<0>(x, y, z));
					vertices.push_back(Vertex::MakeTopFace<1>(x, y, z));
					vertices.push_back(Vertex::MakeTopFace<2>(x, y, z));
					vertices.push_back(Vertex::MakeTopFace<3>(x, y, z));
					vertices.push_back(Vertex::MakeTopFace<4>(x, y, z));
					vertices.push_back(Vertex::MakeTopFace<5>(x, y, z));
				}
				if (y == m_height - 1 || !TestVoxel(x, y + 1, z)) {
					// Add bottom face
					vertices.push_back(Vertex::MakeBottomFace<0>(x, y, z));
					vertices.push_back(Vertex::MakeBottomFace<1>(x, y, z));
					vertices.push_back(Vertex::MakeBottomFace<2>(x, y, z));
					vertices.push_back(Vertex::MakeBottomFace<3>(x, y, z));
					vertices.push_back(Vertex::MakeBottomFace<4>(x, y, z));
					vertices.push_back(Vertex::MakeBottomFace<5>(x, y, z));
				}
				if (z == 0 || !TestVoxel(x, y, z - 1)) {
					// Add front face
					vertices.push_back(Vertex::MakeFrontFace<0>(x, y, z));
					vertices.push_back(Vertex::MakeFrontFace<1>(x, y, z));
					vertices.push_back(Vertex::MakeFrontFace<2>(x, y, z));
					vertices.push_back(Vertex::MakeFrontFace<3>(x, y, z));
					vertices.push_back(Vertex::MakeFrontFace<4>(x, y, z));
					vertices.push_back(Vertex::MakeFrontFace<5>(x, y, z));
				}
				if (z == m_depth - 1 || !TestVoxel(x, y, z + 1)) {
					// Add back face
					vertices.push_back(Vertex::MakeBackFace<0>(x, y, z));
					vertices.push_back(Vertex::MakeBackFace<1>(x, y, z));
					vertices.push_back(Vertex::MakeBackFace<2>(x, y, z));
					vertices.push_back(Vertex::MakeBackFace<3>(x, y, z));
					vertices.push_back(Vertex::MakeBackFace<4>(x, y, z));
					vertices.push_back(Vertex::MakeBackFace<5>(x, y, z));
				}
			}
		}
	}

	reinterpret_cast<VertexBuffer*>(m_chunks.data() + ((p_chunk_index + 1) * m_chunk_size) - sizeof(VertexBuffer))->UpdateVertices(vertices.data(), vertices.size());
}

void ChunkStorage::Render(unsigned int p_chunk_index)
{
	reinterpret_cast<VertexBuffer*>(m_chunks.data() + ((p_chunk_index + 1) * m_chunk_size) - sizeof(VertexBuffer))->Render();
}

void _newchunk1() { ChunkStorage storage(0, 0, 0); storage.NewChunk<false>(); };
void _newchunk2() { ChunkStorage storage(0, 0, 0); storage.NewChunk<true>();  };