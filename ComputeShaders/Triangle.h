#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Model.h"
#include "VertexFormat.h"

class Triangle : public Model
{
public:
	Triangle();
	~Triangle();

	void Create();
	virtual void Update(double dt) override final;
	virtual void Draw(CameraEuler* camera) override final;

private:

	GLuint m_uiModelMatrixUniform;
	GLuint m_uiViewMatrixUniform;
	GLuint m_uiProjectionMatrixUniform;
};

#endif // TRIANGLE_H