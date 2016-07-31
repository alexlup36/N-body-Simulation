#ifndef WINDOWINFO_H
#define WINDOWINFO_H

#include <SDL.h>
#include <string>

#include "Common.h"

struct WindowInfo
{
public:
	WindowInfo();

	WindowInfo(const std::string& windowName,
		int startPosX, int startPosY,
		int windowWidth, int windowHeight,
		bool allowReshape,
		bool fullScreen);

	WindowInfo(const WindowInfo& other);

	void operator=(const WindowInfo& other);

	// Members
	std::string WindowName;
	int WindowWidth, WindowHeight;
	int WindowPosX, WindowPosY;
	bool AllowReshape;
	bool FullScreen;
};

#endif // WINDOWINFO_H