#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ProjectionView;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ProjectionView * vec4(a_Position, 1.0f);
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 f_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	f_Color = texture(u_Texture, v_TexCoord);
};
