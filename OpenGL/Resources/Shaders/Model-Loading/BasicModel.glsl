#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

out vec3 vs_Normal;
out vec3 vs_FragPos;
out vec2 vs_TexCoord;

void main()
{
	gl_Position = u_ProjectionView * u_Model * vec4(a_Position, 1.0f);
	vs_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
	vs_FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	vs_TexCoord = a_TexCoord;
};

#shader fragment
#version 460 core

struct Material {
	sampler2D diffuse1;
	sampler2D diffuse2;
	sampler2D diffuse3;
	sampler2D diffuse4;
	sampler2D specular1;
	sampler2D specular2;
	sampler2D specular3;
	sampler2D specular4;
	float shininess;
};

struct Light {
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

layout(location = 0) out vec4 fs_Color;

in vec3 vs_Normal;
in vec3 vs_FragPos;
in vec2 vs_TexCoord;

uniform Material u_Material;
uniform Light u_Light;

uniform vec3 u_ViewPos;

void main()
{
	vec3 diffuse_vec = vec3(texture(u_Material.diffuse1, vs_TexCoord) + texture(u_Material.diffuse2, vs_TexCoord) + texture(u_Material.diffuse3, vs_TexCoord) + texture(u_Material.diffuse4, vs_TexCoord));
	vec3 specular_vec = vec3(texture(u_Material.specular1, vs_TexCoord) + texture(u_Material.specular2, vs_TexCoord) + texture(u_Material.specular3, vs_TexCoord) + texture(u_Material.specular4, vs_TexCoord));
	// ambient
	vec3 ambient  = u_Light.ambient  * diffuse_vec;

	// Diffuse light
	vec3 normal = normalize(vs_Normal);
	vec3 light_direction = normalize(u_Light.position - vs_FragPos);
	float diffuse_factor = max(dot(normal, light_direction), 0.0f);
	vec3 diffuse = diffuse_factor * u_Light.diffuse * diffuse_vec;
	
	// Specular light
	vec3 view_dir = normalize(u_ViewPos - vs_FragPos);
	vec3 reflect_dir = reflect(-light_direction, normal);
	float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0f), u_Material.shininess);
	vec3 specular = specular_factor * u_Light.specular * specular_vec;

	vec3 color = specular + diffuse + ambient;
	fs_Color = vec4(color, 1.0f);
};
