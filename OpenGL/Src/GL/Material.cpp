#include "Material.h"
#include "Core/Shader.h"

#include <glm/glm.hpp>

void Material::Bind(Shader* shader)
{
	shader->SetUniform3f("u_Material.ambient", ambient_);
	shader->SetUniform3f("u_Material.diffuse", diffuse_);
	shader->SetUniform3f("u_Material.specular", specular_);
	shader->SetUniform1f("u_Material.shininess", shininess_);
}