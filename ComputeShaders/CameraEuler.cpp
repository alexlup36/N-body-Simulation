#include "CameraEuler.h"

#include <string>

// ----------------------------------------------------------------------------

CameraEuler::CameraEuler(const char* cameraName)
{
	// Initialize camera name
	m_psCameraName = new char[strlen(cameraName) + 1];
	strcpy_s(m_psCameraName, strlen(cameraName) + 1, cameraName);

	// Mouse initialization
	m_bMouseDown = false;

	// Mouse rotation initialization
	m_fPitch = 0.0f;
	m_fYaw = 0.0f;

	// Camera position initialization
	m_vEyePosition = glm::vec3(0.0f);

	// View matrix initialization
	UpdateViewMatrix();
}

// ----------------------------------------------------------------------------

CameraEuler::CameraEuler(const char* cameraName,
	const glm::vec3& eyePosition)
{
	// Mouse initialization
	m_bMouseDown = false;

	// Mouse rotation initialization
	m_fPitch = 0.0f;
	m_fYaw = 0.0f;

	// Camera position initialization
	m_vEyePosition = eyePosition;

	// View matrix initialization
	UpdateViewMatrix();
}

// ----------------------------------------------------------------------------

CameraEuler::~CameraEuler()
{
	// Deallocate memory for camera name
	if (m_psCameraName != NULL)
	{
		delete m_psCameraName;
		m_psCameraName = NULL;
	}
}

// ----------------------------------------------------------------------------

void CameraEuler::UpdateViewMatrix()
{
	// Initialize rotation matrices with identity
	glm::mat4 matPitch = glm::mat4(1.0f);
	glm::mat4 matYaw = glm::mat4(1.0f);

	// Create rotation matrices based on the amount we rotated
	matPitch = glm::rotate(matPitch, m_fPitch, rightVector);
	matYaw = glm::rotate(matYaw, m_fYaw, upVector);

	// Calculate the rotation matrix
	glm::mat4 rotationMatrix = matPitch * matYaw;

	// Calculate translation matrix
	glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, -m_vEyePosition);

	// Update the view matrix
	m_mViewMatrix = rotationMatrix * translationMatrix;
}

// ----------------------------------------------------------------------------

void CameraEuler::KeyPress(float dt, const Uint8* keyState)
{
	float fDx = 0.0f;
	float fDz = 0.0f;

	if (keyState[SDL_SCANCODE_W])
	{
		fDz = moveZStep;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		fDz = -moveZStep;
	}
	if (keyState[SDL_SCANCODE_A])
	{
		fDx = -moveXstep;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		fDx = moveXstep;
	}

	// Extract the forward and strafe vector from the view matrix
	glm::vec3 forwardVector(m_mViewMatrix[0][2], m_mViewMatrix[1][2], m_mViewMatrix[2][2]);
	glm::vec3 strafeVector(m_mViewMatrix[0][0], m_mViewMatrix[1][0], m_mViewMatrix[2][0]);

	// Update the eye position vector
	m_vEyePosition += ((-fDz * forwardVector + fDx * strafeVector) * cameraSpeed);
}

// ----------------------------------------------------------------------------

void CameraEuler::MouseMove(float dt, int x, int y)
{
	if (m_bMouseDown == false)
	{
		return;
	}

	// Calculate the mouse offset
	glm::vec2 mouseDelta = glm::vec2(x, y) - m_vMousePosition;

	// Update the angles
	m_fYaw += sensitivityY * dt * mouseDelta.x;
	m_fPitch += sensitivityZ * dt * mouseDelta.y;

	// Update mouse position
	m_vMousePosition = glm::vec2(x, y);
}

// ----------------------------------------------------------------------------

void CameraEuler::MousePressed(Uint32 mouseState, int x, int y)
{
	if (mouseState == SDL_MOUSEBUTTONDOWN)
	{
		m_bMouseDown = true;

		// Update mouse cursor position
		m_vMousePosition.x = (float)x;
		m_vMousePosition.y = (float)y;
	}
	else if (mouseState == SDL_MOUSEBUTTONUP)
	{
		m_bMouseDown = false;
	}
}

// ----------------------------------------------------------------------------

void CameraEuler::SetPerspectiveProjection(float fov, float near, float far)
{
	m_mProjectionMatrix = glm::perspective(fov, (float)WINDOW_WIDTH / WINDOW_HEIGHT, near, far);
}

// ----------------------------------------------------------------------------

void CameraEuler::SetOrthographicProjection(float left,
	float right,
	float bottom,
	float top,
	float near,
	float far)
{
	m_mProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

// ----------------------------------------------------------------------------