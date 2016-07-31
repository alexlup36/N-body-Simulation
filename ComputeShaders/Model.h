#ifndef MODEL_H
#define MODEL_H

#include <SDL.h>
#include <vector>
#include <glm.hpp>

#include "Common.h"
#include "CameraEuler.h"
#include "IObject.h"

class Model : public IObject
{
public:
	Model();
	virtual ~Model();

	virtual void Draw(CameraEuler* camera);
	virtual void Update(double dt);
	virtual void SetProgram(GLuint program);
	virtual void Destroy();

	virtual GLuint GetVao() const;
	virtual const GLuint GetVbo() const;
	virtual const GLuint GetIbo() const;

protected:
	GLuint m_uiVao;
	GLuint m_uiProgram;
	GLuint m_uiVbo;
	GLuint m_uiIbo;
};

#endif // MODEL_H