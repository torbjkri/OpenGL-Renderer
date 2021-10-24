#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

out vec3 vs_Normal;
out vec3 vs_FragPos;

void main()
{
	gl_Position = u_ProjectionView * u_Model * vec4(a_Position, 1.0f);
	vs_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
	vs_FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 f_Color;

in vec3 vs_Normal;
in vec3 vs_FragPos;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_ViewPos;

const float l_AmbientStrength = 0.1f;
const float l_SpecularStrength = 0.5f;

void main()
{
	// Ambient light
	vec3 ambient = l_AmbientStrength * u_LightColor;

	// Diffuse light
	vec3 normal = normalize(vs_Normal);
	vec3 light_direction = normalize(u_LightPosition - vs_FragPos);
	float diffuse_factor = max(dot(normal, light_direction), 0.0f);
	vec3 diffuse = diffuse_factor * u_LightColor;
	
	// Specular light
	vec3 view_dir = normalize(u_ViewPos - vs_FragPos);
	vec3 reflect_dir = reflect(-light_direction, normal);
	float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0f), 256);
	vec3 specular = l_SpecularStrength * specular_factor * u_LightColor;

	vec3 color = (specular + diffuse +  ambient) * u_ObjectColor;
	f_Color = vec4(color, 1.0f);
};