#ifndef __CAMERAMAN_H__
#define __CAMERAMAN_H__

#include "CameraEuler.h"

#include <vector>
#include <SDL.h>

class CameraMan
{

public:
	CameraMan(void);
	~CameraMan(void);
	
	void Update(float dt, SDL_Event e);

	// Create camera
	CameraEuler* CreateCamera(const char* camName, float fFOV, float fNearPlane, float fFarPlane);
	// Set the active camera
	void SetActiveCamera(CameraEuler* newCamera);
	void SetActiveCamera(int index);
	void SetActiveCamera(const char* camName);
	// Get the active camera
	CameraEuler* GetActiveCamera();
	// Get camera
	CameraEuler* GetCamera(const char* camName);
	CameraEuler* GetCamera(int index);

	inline const std::vector<CameraEuler*>& GetCameras() const
	{
		return m_pCameraList;
	}

private:
	CameraEuler* m_pActiveCamera;

	std::vector<CameraEuler*> m_pCameraList;
};

#endif // _CAMERAMAN_H__