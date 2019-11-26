#version 330

in vec2 TexCoords;
uniform vec4 Color;

uniform sampler2D text;
out vec4 color; 

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
	color = Color*sampled;
}
