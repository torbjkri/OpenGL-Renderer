#pragma once

#include "GL/Core/Texture.h"
#include "Mesh.h"

#include <vector>
#include <string>

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
class Shader;

class Model
{
public:
	Model(const std::string path);
	void Render(Shader* shader, const glm::mat4 projectioview, const glm::mat4 model);

private:
	std::vector<Mesh> m_Meshes;

	void LoadModel(const std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene, const std::string& directory);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory);
	Material LoadMaterial(const aiMaterial* material);
};

