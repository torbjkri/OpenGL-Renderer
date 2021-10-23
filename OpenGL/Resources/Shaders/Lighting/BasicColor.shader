#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ProjectionViewModel;

out vec3 vs_Normal;

void main()
{
	gl_Position = u_ProjectionViewModel * vec4(a_Position, 1.0f);
	vs_Normal = a_Normal;
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 f_Color;

in vec3 vs_Normal;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

const float l_AmbientStrength = 0.1f;

void main()
{
	vec3 ambient = l_AmbientStrength * u_LightColor;
	vec3 color = ambient * u_ObjectColor;
	f_Color = vec4(color, 1.0f);
};