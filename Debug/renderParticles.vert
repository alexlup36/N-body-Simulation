#version 450 core

// Particle position
layout (location = 0) in vec4 position;

// Model view project matrix
uniform mat4 mvp;

out float intensity;

void main(void)
{
	// Intensity represents the life of the particle and is going to be used as 
	// the alpha value in the fragment shader
	intensity = position.w;

	gl_Position = mvp * vec4(position.xyz, 1.0f);
}