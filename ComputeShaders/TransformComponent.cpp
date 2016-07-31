#include "TransformComponent.h"

// ----------------------------------------------------------------------------

void TransformComponent::Update(double dt)
{
	glm::mat4 posMatrix = glm::translate(m_vPosition);

	glm::mat4 rotMatrix = glm::rotate(m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 scaleMatrix = glm::scale(m_vScale);

	// Update model matrix
	m_mModelMatrix = posMatrix * rotMatrix * scaleMatrix;
}

// ----------------------------------------------------------------------------

void TransformComponent::Draw(Shader * shader, CameraEuler* camera)
{
}

// ----------------------------------------------------------------------------