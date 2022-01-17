#include "Model.h"

#include "GL/Core/VerticeStructs.h"
#include "Material.h"

#include <iostream>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/material.h"

#include <string>

Model::Model(const std::string path)
{
	LoadModel(path);
}

void Model::Render(Shader* shader, const glm::mat4 projectioview, const glm::mat4 model)
{
	for (auto& mesh : m_Meshes)
		mesh.Render(shader, projectioview, model);
}

void Model::LoadModel(const std::string path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {

		// TODO Need logging library
		std::cout << "Error: Assimp: " << importer.GetErrorString() << std::endl;
		return;
	}

	auto directory = path.substr(0, path.find_last_of('/'));
	
	ProcessNode(scene->mRootNode, scene, directory);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, const std::string& directory)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		// Scene contains actual mesh data, node only contains index
		auto* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene, directory));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene, directory);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory)
{
	std::vector<PositionNormalVertex> vertices;
	std::vector<TriangleIndices> indices;

	// Iterate over vertices and store them
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

		// I always assume we have normals
		vertices.emplace_back(
			PositionNormalVertex{
				{mesh->mVertices[i].x, mesh->mVertices[i].y , mesh->mVertices[i].z },
				{mesh->mNormals[i].x, mesh->mNormals[i].y , mesh->mNormals[i].z }}
		);

		// Just keeping this until I actually need it
		//if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		//{
		//	glm::vec2 vec;
		//	// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
		//	// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
		//	vec.x = mesh->mTextureCoords[0][i].x;
		//	vec.y = mesh->mTextureCoords[0][i].y;
		//	vertex.TexCoords = vec;
		//	// tangent
		//	vector.x = mesh->mTangents[i].x;
		//	vector.y = mesh->mTangents[i].y;
		//	vector.z = mesh->mTangents[i].z;
		//	vertex.Tangent = vector;
		//	// bitangent
		//	vector.x = mesh->mBitangents[i].x;
		//	vector.y = mesh->mBitangents[i].y;
		//	vector.z = mesh->mBitangents[i].z;
		//	vertex.Bitangent = vector;
		//}
		//else
		//	vertex.TexCoords = glm::vec2(0.0f, 0.0f);
	}

	int cnt = 0;
	// Iterate over all faces and extract their indexes
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		auto face = mesh->mFaces[i];
		cnt++;
		// Using triangulate postprocess flag, so this should be ok
		indices.emplace_back(
			TriangleIndices{{
				face.mIndices[0], face.mIndices[1], face.mIndices[2]
			}}
		);
	}

	/*
		TODO: Implement material following the object
	*/


	//material->Get(

	//auto return = material->Get(AI_MATKEY_COLOR_DIFFUSE, ai, )

	Material material = LoadMaterial(scene->mMaterials[mesh->mMaterialIndex]);

	/*
	TODO: Create material class
		- Simple first
	*/


	// Keep this for future use
	//// process materials
	//aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	//// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	//// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	//// Same applies to other texture as the following list summarizes:
	//// diffuse: texture_diffuseN
	//// specular: texture_specularN
	//// normal: texture_normalN
	//
	//// 1. diffuse maps
	//vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//// 2. specular maps
	//vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	//// 3. normal maps
	//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	//// 4. height maps
	//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	
	return Mesh(vertices, indices, material);
}

Material Model::LoadMaterial(const aiMaterial* material)
{
	aiColor3D ambient_color;
	aiColor3D diffuse_color;
	aiColor3D specular_color;
	float shininess;

	material->Get(AI_MATKEY_COLOR_AMBIENT, ambient_color);
	material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse_color);
	material->Get(AI_MATKEY_COLOR_SPECULAR, specular_color);
	material->Get(AI_MATKEY_SHININESS, shininess);

	auto aiToGlm = [](aiColor3D v) {return glm::vec3(v.r , v.g, v.b); };

	return Material{
					.ambient_ = aiToGlm(ambient_color),
					.diffuse_ = aiToGlm(diffuse_color),
					.specular_ = aiToGlm(specular_color),
					.shininess_ = shininess
	};
}

