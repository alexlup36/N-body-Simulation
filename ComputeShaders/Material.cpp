#include "Material.h"

// ------------------------------------------------------------------------

Material::Material(Texture* diffuseTexture,
	Texture* normalTexture,
	Texture* specularTexture,
	Texture* displacementTexture)
{
	m_pDiffuseTexture = diffuseTexture;
	m_pNormalTexture = normalTexture;
	m_pSpecularTexture = specularTexture;
	m_pDisplacementTexture = displacementTexture;
}

// ------------------------------------------------------------------------

Material::~Material()
{
	if (m_pDiffuseTexture != NULL)
	{
		delete m_pDiffuseTexture;
		m_pDiffuseTexture = NULL;
	}

	if (m_pNormalTexture != NULL)
	{
		delete m_pNormalTexture;
		m_pNormalTexture = NULL;
	}

	if (m_pSpecularTexture != NULL)
	{
		delete m_pSpecularTexture;
		m_pSpecularTexture = NULL;
	}

	if (m_pDisplacementTexture != NULL)
	{
		delete m_pDisplacementTexture;
		m_pDisplacementTexture = NULL;
	}
}

// ------------------------------------------------------------------------

void Material::Bind(GLuint program)
{
	if (m_pDiffuseTexture != NULL)
	{
		m_pDiffuseTexture->Bind(0, program);
	}

	if (m_pNormalTexture != NULL)
	{
		m_pNormalTexture->Bind(1, program);
	}

	if (m_pSpecularTexture != NULL)
	{
		m_pSpecularTexture->Bind(2, program);
	}

	if (m_pDisplacementTexture != NULL)
	{
		m_pDisplacementTexture->Bind(3, program);
	}
}

// ------------------------------------------------------------------------