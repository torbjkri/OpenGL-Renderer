#include "Mesh.h"

#include "GL/VerticeStructs.h"
#include "GL/Texture.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexArray.h"
#include "GL/VertexBuffer.h"

#include "RenderableObject.h"

Mesh::Mesh(Shader shader, std::vector<PositionNormalVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	: RenderableObject(shader)
	, vertices_(vertices)
	, indices_(indices)
	, textures_(textures)
{
	InitRenderData();
}

void Mesh::InitRenderData()
{
	vbo_ = VertexBuffer(vertices_);
	ebo_ = ElementBuffer(indices_);

	vao_.Bind();
	vbo_.Bind();
	ebo_.Bind();

	vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao_.LinkAttrib(vbo_, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(offsetof(PositionTextureNormalVertex, m_TexturePosition)));
	vao_.LinkAttrib(vbo_, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(offsetof(PositionNormalVertex, m_VertexNormal)));

	vao_.Unbind();
	vbo_.Unbind();
	ebo_.Unbind();
}

void Mesh::Bind() const
{
	vao_.Bind();

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (int i = 0; i < textures_.size(); i++) {
			std::string number;
		auto type = textures_[i].Type();

		std::string name = TypeToString(type);
		if (type == TextureType::DIFFUSE)
			number = std::to_string(diffuseNr++);
		else if (type == TextureType::SPECULAR)
			number = std::to_string(specularNr++);

		shader_.SetUniform1i("u_Material." + name + number, i);
		textures_[i].Bind(i);
	}
}

void Mesh::Unbind() const
{
	vao_.Unbind();
}
