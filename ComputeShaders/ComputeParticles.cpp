#include "ComputeParticles.h"

#include "glm.hpp"
#include "gtc\constants.hpp"

ComputeParticles::ComputeParticles()
{
}


ComputeParticles::~ComputeParticles()
{
}

void ComputeParticles::Initialize(GLuint computeParticleProgram,
	GLuint renderParticleProgram)
{
	// Get uniform location
	m_uiDtUniform = glGetUniformLocation(computeParticleProgram, "dt");
	m_uiMVPUniform = glGetUniformLocation(renderParticleProgram, "mvp");

	// Create and bind vertex array object
	glGenVertexArrays(1, &m_uiParticlesVAO);
	glBindVertexArray(m_uiParticlesVAO);

	// ------------------------------------------------------------------------
	// Generate position buffer
	glGenBuffers(1, &m_uiPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * 4 * sizeof(float), NULL, GL_DYNAMIC_COPY);

	// Retrive pointer to the start of the buffer
	glm::vec4* positions = (glm::vec4*)glMapBufferRange(GL_ARRAY_BUFFER,
		0,
		PARTICLE_COUNT * 4 * sizeof(float),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	// Fill in the positions
	for (int particleIndex = 0; particleIndex < PARTICLE_COUNT; ++particleIndex)
	{
		/*positions[particleIndex] = glm::vec4(PARTICLE_DISTANCE_CENTER * random(),
			PARTICLE_DISTANCE_CENTER * random(),
			PARTICLE_DISTANCE_CENTER * random(),
			PARTICLE_DISTANCE_CENTER * random());*/

		positions[particleIndex] = glm::vec4(random_vector(-10.0f, 10.0f), random_float());
	}

	// Unmap the position buffer
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	// ------------------------------------------------------------------------
	// Generate velocity buffer
	glGenBuffers(1, &m_uiVelocityBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVelocityBuffer);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_COUNT * 4 * sizeof(float), NULL, GL_DYNAMIC_COPY);

	// Retrieve pointer to the start of the buffer
	glm::vec4* velocities = (glm::vec4*)glMapBufferRange(GL_ARRAY_BUFFER,
		0,
		PARTICLE_COUNT * 4 * sizeof(float),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	// Fill in the velocities
	for (int particleIndex = 0; particleIndex < PARTICLE_COUNT; ++particleIndex)
	{
		/*velocities[particleIndex] = glm::vec4(PARTICLE_VELOCITY_MULTI * random(), 
			PARTICLE_VELOCITY_MULTI * random(), 
			PARTICLE_VELOCITY_MULTI * random(), 
			PARTICLE_VELOCITY_MULTI * random());*/

		velocities[particleIndex] = glm::vec4(random_vector(-0.1f, 0.1f), 0.0f);
	}

	// Unmap the velocity buffer
	glUnmapBuffer(GL_ARRAY_BUFFER);

	// ------------------------------------------------------------------------
	// Generate the textures buffer objects
	glGenTextures(1, &m_uiPositionTextureBufferObject);
	glGenTextures(1, &m_uiVelocityTextureBufferObject);

	// Set the data for the position texture buffer object 
	glBindTexture(GL_TEXTURE_BUFFER, m_uiPositionTextureBufferObject);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, m_uiPositionBuffer);

	// Set the data for the velocity texture buffer object
	glBindTexture(GL_TEXTURE_BUFFER, m_uiVelocityTextureBufferObject);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, m_uiVelocityBuffer);

	// ------------------------------------------------------------------------
	// Initialize the attractor's masses
	for (int attractorIndex = 0; attractorIndex < ATTRACTORS_COUNT; ++attractorIndex)
	{
		//m_vAttractorMasses[attractorIndex] = ATTRACTORS_MASS_SCALE * (random() + 1.0f);

		m_vAttractorMasses[attractorIndex] = 1000.5f + random_float() * 0.5f;
	}

	// Setup attractor uniform buffer
	glGenBuffers(1, &m_uiAttractorBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uiAttractorBuffer);
	glBufferData(GL_UNIFORM_BUFFER, ATTRACTORS_COUNT * 4 * sizeof(float), NULL, GL_STATIC_DRAW);

	// Bind buffer to the binding point 0
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_uiAttractorBuffer);
}

void ComputeParticles::Draw(float dt,
	CameraEuler* camera, 
	GLuint computeParticleProgram,
	GLuint renderParticleProgram)
{
	// ------------------------------------------------------------------------
	// Update attractors

	// Update the position of the attractors and copy their masses
	glm::vec4* attractors = (glm::vec4*)glMapBufferRange(GL_UNIFORM_BUFFER,
		0,
		ATTRACTORS_COUNT * 4 * sizeof(float),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	// Update the positions of the attractors
	for (int iAttractorIndex = 0; iAttractorIndex < ATTRACTORS_COUNT; ++iAttractorIndex)
	{
		attractors[iAttractorIndex] = glm::vec4(sinf(dt * (float)(iAttractorIndex + 4) * 7.5f * 20.0f) * 50.0f,
			cosf(dt * (float)(iAttractorIndex + 7) * 3.9f * 20.0f) * 50.0f,
			sinf(dt * (float)(iAttractorIndex + 3) * 5.3f * 20.0f) * cosf(dt * (float)(iAttractorIndex + 5) * 9.1f) * 100.0f,
			m_vAttractorMasses[iAttractorIndex]);
	}

	// Unmap the attractors vector
	glUnmapBuffer(GL_UNIFORM_BUFFER);
	// ------------------------------------------------------------------------
	// If dt is too large cap it
	if (dt > 2.0f)
	{
		dt = 2.0f;
	}

	// ------------------------------------------------------------------------
	// Run the compute shader

	// Use the compute shader to update the position and velocities of the particles
	glUseProgram(computeParticleProgram);

	// Set delta time
	glUniform1f(m_uiDtUniform, dt);
	// Bind the position and velocity buffers
	glBindImageTexture(0, m_uiVelocityTextureBufferObject, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glBindImageTexture(1, m_uiPositionTextureBufferObject, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

	// Dispatch compute shader
	glDispatchCompute(PARTICLE_GROUP_COUNT, 1, 1);

	// Wait for the compute shader to finish the execution
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	// ------------------------------------------------------------------------

	// Setup MVP matrix for rendering the particles
	glm::mat4 mvp = camera->ProjectionMatrix() * camera->ViewMatrix() * glm::mat4(1.0f);

	glDisable(GL_DEPTH_TEST);
	glUseProgram(renderParticleProgram);
	glUniformMatrix4fv(m_uiMVPUniform, 1, GL_FALSE, &mvp[0][0]);
	glBindVertexArray(m_uiParticlesVAO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}
