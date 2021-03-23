#pragma once

class TextureArray
{
public:
	TextureArray(const char* p_file_name, int p_width, int p_height);
	TextureArray(const TextureArray&) = delete;
	~TextureArray();

	void Bind(unsigned int p_slot);
private:
	unsigned int m_texture_array;
};