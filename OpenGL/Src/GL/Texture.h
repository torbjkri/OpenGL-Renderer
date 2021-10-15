#pragma once
#include <string>
#include <glad/glad.h>

class Texture
{
private:
	GLuint m_RendererID;
	std::string m_FilePath;
	int m_Width;
	int m_Height;

public:
	Texture(const std::string filePath);
	~Texture();

	void Bind(const unsigned int slot) const;
	void Unbind() const;
};

