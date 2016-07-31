#ifndef QUAD_H
#define QUAD_H

#include "Model.h"
#include "VertexFormat.h"

class Quad : public Model
{
public:
	Quad();
	~Quad();

	void Create();
	void CreateScreenPercentage(float percentage);
	virtual void Update(double dt) override final;
	virtual void Draw(CameraEuler* camera) override final;

private:

	GLuint m_uiModelMatrixUniform;
	GLuint m_uiViewMatrixUniform;
	GLuint m_uiProjectionMatrixUniform;
};

#endif // QUAD_H