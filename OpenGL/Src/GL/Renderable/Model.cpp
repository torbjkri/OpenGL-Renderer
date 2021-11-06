#include "Model.h"
#include "Mesh.h"
#include "GL/ResourceManager.h"

#include <iostream>

Model::Model(const std::string filepath)
{
	LoadModel(filepath);
}

void Model::LoadModel(std::string filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR:ASSIMP" << importer.GetErrorString() << std::endl;
		return;
	}

	modelDirectory_ = filepath.substr(0, filepath.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<PositionTextureNormalVertex> vertices;
	vertices.reserve(mesh->mNumVertices);
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		vertices.push_back(
			{ {
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z},
			{
			mesh->mTextureCoords[0][i].x,
			mesh->mTextureCoords[0][i].y},
			{
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z}
			});
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material,
			aiTextureType_DIFFUSE,
			TextureType::DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = LoadMaterialTextures(material,
			aiTextureType_SPECULAR, TextureType::SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	
	Mesh myMesh(ResourceManager::GetInstance()->GetShader("basic"), vertices, indices, textures);
	return myMesh;
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, TextureType texType)
{
	std::vector<Texture> textures(material->GetTextureCount(type));

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);
		ResourceManager::GetInstance()->LoadTexture(modelDirectory_ + "/" + str.C_Str(), std::string(str.C_Str()), texType);
		textures.push_back(ResourceManager::GetInstance()->GetTexture(std::string(str.C_Str())));
	}

	return textures;
}
