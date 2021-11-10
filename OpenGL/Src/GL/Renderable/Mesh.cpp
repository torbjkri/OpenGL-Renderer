#include "Mesh.h"


#include <GL/Core/VertexArray.h>
#include <GL/Core/ElementBuffer.h>
#include <GL/Core/VertexBuffer.h>
#include <GL/Core/VerticeStructs.h>
#include <GL/Core/Shader.h>
#include <GL/Core/Texture.h>

#include "RenderableObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(Shader shader, std::vector<PositionTextureNormalVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
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
	vao_.LinkAttrib(vbo_, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(offsetof(PositionTextureNormalVertex, m_VertexNormal)));

	vao_.Unbind();
	vbo_.Unbind();
	ebo_.Unbind();
}

void Mesh::Bind() const
{
	vao_.Bind();
	shader_.Bind();

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

    shader_.SetUniform1f("u_Material.shininess", 32.0f);

	glm::mat4 model_mat = glm::translate(glm::mat4(1.0), position_);
	model_mat = model_mat * orientation_mat_;
	model_mat = glm::scale(model_mat, glm::vec3(scale_));

	shader_.SetUniformMatrix4fv("u_Model", 1, model_mat);
}

void Mesh::Unbind() const
{
	vao_.Unbind();
}
