#pragma once

#include "GL/VerticeStructs.h"
#include "GL/Texture.h"
#include "GL/Shader.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexArray.h"
#include "GL/VertexBuffer.h"

#include "RenderableObject.h"

#include <vector>

class Mesh : public RenderableObject {
public:
	std::vector<PositionNormalVertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<Texture> textures_;

	Mesh(Shader shader, std::vector<PositionNormalVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void InitRenderData() override;

	void Bind() const override;
	void Unbind() const override;
};
