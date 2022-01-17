#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
// TODO: Use Normal matrix instead of complicaated math

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

out vec3 vs_Normal;
out vec3 vs_FragPos;

void main()
{
	vs_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
	vs_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
	gl_Position = u_ProjectionView * vec4(vs_FragPos, 1.0);
};

#shader fragment
#version 460 core

// TODO: Split shaders, this is hard to read!

struct Material {
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material u_Material;
uniform Light u_Light;
uniform vec3 u_ViewPos;

in vec3 vs_Normal;
in vec3 vs_FragPos;

layout(location = 0) out vec4 f_Color;


void main()
{
	// Ambient
	vec3 ambient = u_Light.ambient * u_Material.ambient;

	// Diffuse 
	vec3 norm = normalize(vs_Normal);
	vec3 lightDir = normalize(u_Light.position - vs_FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * (diff * u_Material.diffuse);

	// Specular
	vec3 viewDir = normalize(u_ViewPos - vs_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * (spec * u_Material.specular);

	vec3 result = ambient + diffuse + specular;

	f_Color = vec4(result, 1.0);
};