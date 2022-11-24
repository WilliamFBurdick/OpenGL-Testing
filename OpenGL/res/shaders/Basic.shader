#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 vColor;

out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
	v_Color = vec4(vColor, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
	vec4 texColor = texture(u_Texture1, v_TexCoord) * texture(u_Texture2, v_TexCoord);
	color = texColor * v_Color * u_Color;
};