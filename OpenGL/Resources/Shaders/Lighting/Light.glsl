#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_ProjectionView * u_Model * vec4(a_Position, 1.0f);
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 f_Color;

uniform vec3 u_LightColor;

void main()
{
	f_Color = vec4(u_LightColor, 1.0f);
};
