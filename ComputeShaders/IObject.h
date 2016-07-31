#ifndef IOBJECT_H
#define IOBJECT_H

#include <SDL.h>
#include <vector>
#include <glm.hpp>

#include "Common.h"
#include "CameraEuler.h"

class IObject
{
public:
	virtual ~IObject() = 0;

	virtual void Draw(CameraEuler* camera) = 0;
	virtual void Update(double dt) = 0;
	virtual void SetProgram(GLuint shaderName) = 0;
	virtual void Destroy() = 0;

	virtual GLuint GetVao() const = 0;
	virtual const GLuint GetVbo() const = 0;
	virtual const GLuint GetIbo() const = 0;
};

inline IObject::~IObject()
{

}

#endif // IOBJECT_H