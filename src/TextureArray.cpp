#include "TextureArray.hpp"
#include <stb_image.h>
#include <glm/common.hpp>
#include <iostream>
#include "GL.hpp"

TextureArray::TextureArray(const char* p_file_name, int p_width, int p_height)
{
	GL::CreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_texture_array);

	GL::TextureParameteri(m_texture_array, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GL::TextureParameteri(m_texture_array, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int image_width, image_height, image_channels;
	stbi_uc* image_data = stbi_load(p_file_name, &image_width, &image_height, &image_channels, 0);
	if (!image_data) {
		std::cerr << "TextureArray::TextureArray: Failed to load file (" << p_file_name << ")\n";
		return;
	}

	GLenum format;
	GLenum internal_format;
	switch (image_channels) {
		case 1: format = GL_RED;  internal_format = GL_R8;    break;
		case 2: format = GL_RG;   internal_format = GL_RG8;   break;
		case 3: format = GL_RGB;  internal_format = GL_RGB8;  break;
		case 4: format = GL_RGBA; internal_format = GL_RGBA8; break;
		default:
			format = GL_NONE;
			std::cerr << "TextureArray::TextureArray: Unsupported nubmer of channels (" << image_channels << ") in file (" << p_file_name << ")\n";
			return;
	}

	int layer_count = glm::floor(image_height / p_height);

	GL::TextureStorage3D(m_texture_array, 1, internal_format, p_width, p_height, layer_count);
	for (int layer = 0; layer < layer_count; layer++) {
		GL::TextureSubImage3D(m_texture_array, 0, 0, 0, layer, p_width, p_height, 1, format, GL_UNSIGNED_BYTE, image_data + (p_width * p_height * image_channels * layer));
	}

	stbi_image_free(image_data);
}

TextureArray::~TextureArray()
{
	GL::DeleteTextures(1, &m_texture_array);
}

void TextureArray::Bind(unsigned int p_slot)
{
	GL::BindTextureUnit(p_slot, m_texture_array);
}