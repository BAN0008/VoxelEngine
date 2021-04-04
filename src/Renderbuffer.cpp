#include "Renderbuffer.hpp"
#include "GL.hpp"

Renderbuffer::Renderbuffer(Format p_format, int p_width, int p_height)
{
	GL::CreateRenderbuffers(1, &m_renderbuffer);
	GL::NamedRenderbufferStorage(m_renderbuffer, p_format, p_width, p_height);
}

Renderbuffer::~Renderbuffer()
{
	GL::DeleteRenderbuffers(1, &m_renderbuffer);
}