#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "GL/Texture.h"

#include <string>
#include <vector>

struct Model
{
public:
	Model(const std::string filepath);

	std::vector<Mesh> meshes_;
	std::string modelDirectory_;

	void LoadModel(std::string filepath);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* material,
		aiTextureType type, TextureType texType);
};

