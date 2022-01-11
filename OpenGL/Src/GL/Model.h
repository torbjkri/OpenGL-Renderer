#pragma once

#include "GL/Core/Texture.h"
#include "Mesh.h"

#include <vector>
#include <string>

struct aiScene;
struct aiNode;
struct aiMesh;

class Model
{
public:
	std::vector<Mesh> m_Meshes;

	Model(const std::string path);

private:
	void LoadModel(const std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene, const std::string& directory);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory);

};

