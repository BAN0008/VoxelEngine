#pragma once

class Framebuffer;

class Texture
{
public:
	enum Format {
		U32     = 0x8236,
		Depth16 = 0x81a5,
		Depth24 = 0x81a6,
		Depth32 = 0x81a7
	};

	Texture(Format p_format, int p_width, int p_height);
	Texture(const Texture&) = delete;
	~Texture();
private:
	friend Framebuffer;
	unsigned int m_texture;
};