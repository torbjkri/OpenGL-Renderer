#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;

uniform float u_Size;
uniform mat4 u_ProjectionView;


void main()
{
	gl_Position = u_ProjectionView * vec4(u_Size * a_Position, 1.0f);
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 f_Color;

uniform vec4 u_Color;

void main()
{
	f_Color = u_Color;
};