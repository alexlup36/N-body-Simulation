#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#define GLM_FORCE_RADIANS 1

#include <glm.hpp>
#include <gtx\transform.hpp>

#include "Common.h"
#include "CameraEuler.h"

class Shader;

class TransformComponent
{
public:
	TransformComponent(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
		: m_vPosition( pos ), m_vRotation( rot ), m_vScale( scale ) {}

	inline glm::mat4 GetModel() const
	{
		return m_mModelMatrix;
	}

	inline glm::vec3& GetPos()		{ return m_vPosition; }
	inline glm::vec3& GetRotation() { return m_vRotation; }
	inline glm::vec3& GetScale()	{ return m_vScale; }

	inline void SetPos( const glm::vec3& pos )		{ m_vPosition = pos; }
	inline void SetRotation( const glm::vec3& rot )	{ m_vRotation = rot; }
	inline void SetScale( const glm::vec3& scale )	{ m_vScale = scale; }
		
	inline void SetPos( GLfloat x, GLfloat y, GLfloat z )		
	{
		m_vPosition.x = x; 
		m_vPosition.y = y; 
		m_vPosition.z = z; 
	}
	inline void SetRotation( GLfloat x, GLfloat y, GLfloat z )	
	{ 
		m_vRotation.x = x;
		m_vRotation.y = y;
		m_vRotation.z = z; 
	}
	inline void SetScale( GLfloat x, GLfloat y, GLfloat z )	
	{ 
		m_vScale.x = x; 
		m_vScale.y = y; 
		m_vScale.z = z; 
	}
protected:

private:
	glm::vec3 m_vPosition;
	glm::vec3 m_vRotation;
	glm::vec3 m_vScale;

	glm::mat4 m_mModelMatrix;

	// Inherited via BaseComponent
	virtual void Update(double dt);

	virtual void Draw(Shader* shader, CameraEuler* camera);
};


#endif