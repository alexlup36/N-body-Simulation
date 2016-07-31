#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"

class Material
{
public:

	// ------------------------------------------------------------------------

	Material(Texture* diffuseTexture, 
		Texture* normalTexture = NULL,
		Texture* specularTexture = NULL,
		Texture* displacementTexture = NULL);

	// ------------------------------------------------------------------------

	~Material();

	// ------------------------------------------------------------------------

	void Bind(GLuint program);

private:
	Texture* m_pDiffuseTexture;
	Texture* m_pNormalTexture;
	Texture* m_pSpecularTexture;
	Texture* m_pDisplacementTexture;
};

#endif // MATERIAL_H