#include "MeshRendererComponent.h"

// ----------------------------------------------------------------------------

MeshRendererComponent::MeshRendererComponent(Model* model, Material* material)
	: m_pModel(model), m_pMaterial(material) {}

// ----------------------------------------------------------------------------

MeshRendererComponent::~MeshRendererComponent()
{
	if (m_pModel != NULL)
	{
		delete m_pModel;
		m_pModel = NULL;
	}

	if (m_pMaterial != NULL)
	{
		delete m_pMaterial;
		m_pMaterial = NULL;
	}
}

// ----------------------------------------------------------------------------

void MeshRendererComponent::Update(double dt)
{
}

// ----------------------------------------------------------------------------

void MeshRendererComponent::Draw(Shader* shader, CameraEuler* camera)
{
	glUseProgram(shader->ProgramID());

	m_pModel->Draw(camera);

	glUseProgram(0);

	// Set uniforms
}

// ----------------------------------------------------------------------------