#ifndef MESHRENDERERCOMPONENT_H
#define MESHRENDERERCOMPONENT_H

#include "Common.h"
#include "Shader.h"

#include "Model.h"
#include "Material.h"
#include "CameraEuler.h"

class MeshRendererComponent
{
public:
	MeshRendererComponent(Model* model, Material* material);
	~MeshRendererComponent();

	// Inherited via BaseComponent
	virtual void Update(double dt);
	virtual void Draw(Shader * shader, CameraEuler* camera);

	inline const Shader* GetShader() const { return m_pShader; }
	inline const void SetShader(Shader* newShader) { m_pShader = newShader; }

private:

	Model* m_pModel;
	Material* m_pMaterial;
	Shader* m_pShader;
};

#endif MESHRENDERERCOMPONENT_H