#ifndef __COMPUTE_PARTICLES_H__
#define __COMPUTE_PARTICLES_H__

#include "Common.h"
#include "CameraEuler.h"

class ComputeParticles
{
public:
	ComputeParticles();
	~ComputeParticles();

	void Initialize(GLuint computeParticleProgram,
		GLuint renderParticleProgram);
	void Draw(float dt,
		CameraEuler* camera,
		GLuint computeParticleProgram,
		GLuint renderParticleProgram);

private:

	inline const float random() const { return (float)((double)rand() / (RAND_MAX)); }

	static inline float random_float()
	{
		float res;
		unsigned int tmp;
		static unsigned int seed = 0xFFFF0C59;

		seed *= 16807;

		tmp = seed ^ (seed >> 4) ^ (seed << 15);

		*((unsigned int *)&res) = (tmp >> 9) | 0x3F800000;

		return (res - 1.0f);
	}

	static glm::vec3 random_vector(float minmag = 0.0f, float maxmag = 1.0f)
	{
		glm::vec3 randomvec(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
		randomvec = normalize(randomvec);
		randomvec *= (random_float() * (maxmag - minmag) + minmag);

		return randomvec;
	}

	// Particle const data
	static const int PARTICLE_GROUP_SIZE		= 128;
	static const int PARTICLE_GROUP_COUNT		= 32000;
	static const int PARTICLE_COUNT				= PARTICLE_GROUP_COUNT * PARTICLE_GROUP_SIZE;
	static const int PARTICLE_DISTANCE_CENTER	= 10;
	static const int PARTICLE_VELOCITY_MULTI	= 1;

	// Attractor const data
	static const int ATTRACTORS_COUNT			= 64;
	static const int ATTRACTORS_MASS_SCALE		= 1;

	// Array of attractor's masses
	float m_vAttractorMasses[ATTRACTORS_COUNT];

	GLuint m_uiParticlesVAO;

	GLuint m_uiPositionBuffer;
	GLuint m_uiVelocityBuffer;

	GLuint m_uiPositionTextureBufferObject;
	GLuint m_uiVelocityTextureBufferObject;

	GLuint m_uiAttractorBuffer;

	// Shader uniforms
	GLuint m_uiAttractorBufferUniform;
	GLuint m_uiDtUniform;
	GLuint m_uiMVPUniform;
};

#endif // __COMPUTE_PARTICLES_H__