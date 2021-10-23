#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ProjectionViewModel;

void main()
{
	gl_Position = u_ProjectionViewModel * vec4(a_Position, 1.0f);
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 f_Color;

uniform vec3 u_ObjectColor;

void main()
{
	f_Color = vec4(u_ObjectColor, 1.0f);
};
