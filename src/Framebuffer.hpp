#pragma once
#include "Texture.hpp"
#include "Renderbuffer.hpp"

class Framebuffer
{
public:
	Framebuffer();
	Framebuffer(const Framebuffer&) = delete;
	~Framebuffer();

	void AttachNone(int p_width, int p_height);
	void AttachColor(int p_slot, Texture& p_texture);
	void AttachColor(int p_slot, Renderbuffer& p_renderbuffer);
	void AttachDepth(Texture& p_texture);
	void AttachDepth(Renderbuffer& p_renderbuffer);
	void Bind();
	static void BindDefault();
private:
	unsigned int m_framebuffer;
};