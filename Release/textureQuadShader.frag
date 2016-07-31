#version 450 core

in vec2 tex;

out vec4 color;

uniform sampler2D diffuseSampler;

void main(void)
{
	color = texture(diffuseSampler, tex);
}