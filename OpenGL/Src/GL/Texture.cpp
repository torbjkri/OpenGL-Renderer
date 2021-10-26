#include "Texture.h"
#include "stb_image/stb_image.h"

#include <glad/glad.h>

#include <filesystem>
#include <cassert>

#include <iostream>
#include <format>

namespace fs = std::filesystem;

Texture::Texture(const std::string filePath)
	: m_RendererID(0)
	, m_FilePath(filePath)
	, m_Width(0)
	, m_Height(0)
{
	stbi_set_flip_vertically_on_load(true);
	auto absPath = fs::current_path().string() + "\\" + filePath;
	int n;
	unsigned char* data = stbi_load(absPath.c_str(), &m_Width, &m_Height, &n, 0);
	assert(data);
	
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (n == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	assert(m_RendererID > 0);
}

void Texture::Bind(const unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() const
{
	glDeleteTextures(1, &m_RendererID);
}
