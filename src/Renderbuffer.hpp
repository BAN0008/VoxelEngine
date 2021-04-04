#pragma once

class Framebuffer;

class Renderbuffer
{
public:
	enum Format {
		Depth16 = 0x81a5,
		Depth24 = 0x81a6,
		Depth32 = 0x81a7
	};

	Renderbuffer(Format p_format, int p_width, int p_height);
	Renderbuffer(const Renderbuffer&) = delete;
	~Renderbuffer();
private:
	friend Framebuffer;
	unsigned int m_renderbuffer;
};