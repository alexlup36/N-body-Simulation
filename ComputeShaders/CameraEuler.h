#ifndef CAMERAEULER_H
#define CAMERAEULER_H

#include "Common.h"
#include "glm.hpp"
#include "gtx\rotate_vector.hpp"
#include "SDL.h"

class CameraEuler
{
public:
	CameraEuler(const char* cameraName);
	CameraEuler(const char* cameraName,
		const glm::vec3& eyePosition);
	~CameraEuler();

	// View matrix
	void UpdateViewMatrix();
	inline const glm::mat4& ViewMatrix() const 
	{
		return m_mViewMatrix;
	}

	void SetPerspectiveProjection(float fov, float near, float far);
	void SetOrthographicProjection(float left, 
		float right, 
		float bottom, 
		float top, 
		float near, 
		float far);
	inline const glm::mat4 ProjectionMatrix() const
	{
		return m_mProjectionMatrix;
	}

	void KeyPress(float dt, const Uint8* keyState);

	void MouseMove(float dt, int x, int y);

	void MousePressed(Uint32 mouseState, int x, int y);

	inline const char* CameraName() const
	{
		return m_psCameraName;
	}

private:

	bool m_bMouseDown;

	float m_fPitch;
	float m_fYaw;

	glm::vec2 m_vMousePosition;

	glm::vec3 m_vEyePosition;

	glm::mat4 m_mViewMatrix;
	glm::mat4 m_mProjectionMatrix;

	// Camera name
	char* m_psCameraName;

	// Constant vectors
	const glm::vec3 rightVector = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	const float moveZStep = 2.0f;
	const float moveXstep = 2.0f;

	const float sensitivityZ = 0.1f;
	const float sensitivityY = 0.1f;

	const float cameraSpeed = 0.1f;

};

#endif // CAMERAEULER_H