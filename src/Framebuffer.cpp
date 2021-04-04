#include "Framebuffer.hpp"
#include "GL.hpp"

Framebuffer::Framebuffer()
{
	GL::CreateFramebuffers(1, &m_framebuffer);
};

Framebuffer::~Framebuffer()
{
	GL::DeleteFramebuffers(1, &m_framebuffer);
}

void Framebuffer::AttachNone(int p_width, int p_height)
{
	GL::NamedFramebufferParameteri(m_framebuffer, GL_FRAMEBUFFER_DEFAULT_WIDTH, p_width);
	GL::NamedFramebufferParameteri(m_framebuffer, GL_FRAMEBUFFER_DEFAULT_HEIGHT, p_height);
	GL::NamedFramebufferParameteri(m_framebuffer, GL_FRAMEBUFFER_DEFAULT_LAYERS, 0);
	GL::NamedFramebufferParameteri(m_framebuffer, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 0);
	GL::NamedFramebufferParameteri(m_framebuffer, GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS, 0);
}

void Framebuffer::AttachColor(int p_slot, Texture& p_texture)
{
	GL::NamedFramebufferTexture(m_framebuffer, GL_COLOR_ATTACHMENT0 + p_slot, p_texture.m_texture, 0);
}

void Framebuffer::AttachColor(int p_slot, Renderbuffer& p_renderbuffer)
{
	GL::NamedFramebufferRenderbuffer(m_framebuffer, GL_COLOR_ATTACHMENT0 + p_slot, GL_RENDERBUFFER, p_renderbuffer.m_renderbuffer);
}

void Framebuffer::AttachDepth(Texture& p_texture)
{
	GL::NamedFramebufferTexture(m_framebuffer, GL_DEPTH_ATTACHMENT, p_texture.m_texture, 0);
}

void Framebuffer::AttachDepth(Renderbuffer& p_renderbuffer)
{
	GL::NamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, p_renderbuffer.m_renderbuffer);
}

void Framebuffer::Bind()
{
	GL::BindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebuffer);
}

void Framebuffer::BindDefault()
{
	GL::BindFramebuffer(GL_FRAMEBUFFER, 0);
}