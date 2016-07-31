#include "CameraMan.h"

#include <iostream>

// ----------------------------------------------------------------------------

CameraMan::CameraMan(void)
{
	m_pActiveCamera = NULL;
}

// ----------------------------------------------------------------------------

CameraMan::~CameraMan(void)
{
	std::vector<CameraEuler*>::const_iterator camIterator = m_pCameraList.begin();

	while (camIterator != m_pCameraList.end())
	{
		CameraEuler* tmp = *camIterator;

		if (tmp != NULL)
		{
			delete tmp;
			tmp = NULL;
		}

		camIterator++;
	}
}

// ----------------------------------------------------------------------------

// Create camera
CameraEuler* CameraMan::CreateCamera(const char* camName, float fFOV, float fNearPlane, float fFarPlane)
{
	// Create a new default camera
	CameraEuler* newCamera = new CameraEuler(camName);

	// Set the projection matrix for the camera
	newCamera->SetPerspectiveProjection(fFOV, fNearPlane, fFarPlane);

	// If no active camera set it to the new created camera
	if (!m_pActiveCamera)
	{
		m_pActiveCamera = newCamera;
	}

	// Add the new created camera to the camera list
	m_pCameraList.push_back(newCamera);

	// Return the newly created camera
	return newCamera;
}

// ----------------------------------------------------------------------------

// Set the active camera
void CameraMan::SetActiveCamera(CameraEuler* newCamera)
{
	if (newCamera != NULL)
	{
		m_pActiveCamera = newCamera;
	}
}

// ----------------------------------------------------------------------------

void CameraMan::SetActiveCamera(int index)
{
	CameraEuler* tempCamera = m_pCameraList[index];

	if (tempCamera != NULL)
	{
		m_pActiveCamera = tempCamera;
	}
}

// ----------------------------------------------------------------------------

void CameraMan::SetActiveCamera(const char* camName)
{
	// Iterator for the list of cameras
	std::vector<CameraEuler*>::const_iterator camIterator = m_pCameraList.begin();

	while (camIterator != m_pCameraList.end())
	{
		if (*camIterator != NULL)
		{
			if (strcmp((*camIterator)->CameraName(), camName) == 0)
			{
				m_pActiveCamera = *camIterator;
			}
		}
		
		camIterator++;
	}
}

// ----------------------------------------------------------------------------

// Get the active camera
CameraEuler* CameraMan::GetActiveCamera()
{
	return m_pActiveCamera;
}

// ----------------------------------------------------------------------------

// Get camera
CameraEuler* CameraMan::GetCamera(const char* camName)
{
	// Iterator for the list of cameras
	std::vector<CameraEuler*>::const_iterator camIterator = m_pCameraList.begin();

	while (camIterator != m_pCameraList.end())
	{
		if (strcmp((*camIterator)->CameraName(), camName) == 0)
		{
			return *camIterator;
		}

		camIterator++;
	}

	return NULL;
}

// ----------------------------------------------------------------------------

CameraEuler* CameraMan::GetCamera(int index)
{
	return m_pCameraList[index];
}

// ----------------------------------------------------------------------------

// Update the camera
void CameraMan::Update(float dt, SDL_Event e)
{
	// Get mouse cursor position
	int x, y;
	SDL_GetMouseState(&x, &y);

	//SDL_PumpEvents();
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if (m_pActiveCamera != NULL)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN ||
			e.type == SDL_MOUSEBUTTONUP)
		{
			m_pActiveCamera->MousePressed(e.type, x, y);
		}

		if (keyState[SDL_SCANCODE_S] || 
			keyState[SDL_SCANCODE_W] || 
			keyState[SDL_SCANCODE_A] || 
			keyState[SDL_SCANCODE_D])
		{
			m_pActiveCamera->KeyPress(dt, keyState);
		}
		if (e.type == SDL_MOUSEMOTION)
		{
			m_pActiveCamera->MouseMove(dt, x, y);
		}

		m_pActiveCamera->UpdateViewMatrix();
	}
}

// ----------------------------------------------------------------------------