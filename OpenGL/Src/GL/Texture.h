#pragma once
#include <string>
#include <glad/glad.h>

enum class TextureType {UNSPECIFIED, SPECULAR, DIFFUSE};
std::string TypeToString(const TextureType type);

class Texture
{
private:
	GLuint m_RendererID;
	std::string m_FilePath;
	TextureType m_Type;
	int m_Width;
	int m_Height;

public:

	enum class Type {UNSPECIFIED, SPECULAR, DIFFUSE};

	Texture() = default;
	Texture(const std::string filePath, const TextureType type = TextureType::UNSPECIFIED);

	void Bind(const unsigned int slot) const;
	void Unbind() const;
	void Delete() const;
	TextureType Type() const;
};

