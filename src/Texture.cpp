#include "Texture.hpp"
#include "GL.hpp"

Texture::Texture(Format p_format, int p_width, int p_height)
{
	GL::CreateTextures(GL_TEXTURE_2D, 1, &m_texture);
	GL::TextureStorage2D(m_texture, 1, p_format, p_width, p_height);
}

Texture::~Texture()
{
	GL::DeleteTextures(1, &m_texture);
}