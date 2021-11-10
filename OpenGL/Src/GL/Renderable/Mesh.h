#pragma once


#include <GL/Core/VertexArray.h>
#include <GL/Core/ElementBuffer.h>
#include <GL/Core/VertexBuffer.h>
#include <GL/Core/VerticeStructs.h>
#include <GL/Core/Shader.h>
#include <GL/Core/Texture.h>

#include "RenderableObject.h"

#include <vector>

struct Mesh : public RenderableObject {
public:
	std::vector<PositionTextureNormalVertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<Texture> textures_;

	Mesh(Shader shader, std::vector<PositionTextureNormalVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void InitRenderData() override;

	void Bind() const override;
	void Unbind() const override;
};
