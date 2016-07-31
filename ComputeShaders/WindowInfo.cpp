#include "WindowInfo.h"

WindowInfo::WindowInfo()
{
	// Default constructor
	this->WindowName	= "OpenGL Window";

	this->WindowWidth	= WINDOW_WIDTH;
	this->WindowHeight	= WINDOW_HEIGHT;
	this->WindowPosX	= SDL_WINDOWPOS_UNDEFINED;
	this->WindowPosY	= SDL_WINDOWPOS_UNDEFINED;

	this->AllowReshape	= true;
	this->FullScreen	= false;
}

WindowInfo::WindowInfo(const std::string& windowName, 
	int startPosX, 
	int startPosY, 
	int windowWidth, 
	int windowHeight, 
	bool allowReshape, 
	bool fullScreen)
{
	// Constructor
	this->WindowName	= windowName;

	this->WindowWidth	= windowWidth;
	this->WindowHeight	= windowHeight;
	this->WindowPosX	= startPosX;
	this->WindowPosY	= startPosY;

	this->AllowReshape	= allowReshape;
	this->FullScreen	= fullScreen;
}

WindowInfo::WindowInfo(const WindowInfo& other)
{
	// Copy constructor
	this->WindowName	= other.WindowName;

	this->WindowWidth	= other.WindowWidth;
	this->WindowHeight	= other.WindowHeight;
	this->WindowPosX	= other.WindowPosX;
	this->WindowPosY	= other.WindowPosY;

	this->AllowReshape	= other.AllowReshape;
	this->FullScreen	= other.FullScreen;
}

void WindowInfo::operator=(const WindowInfo& other)
{
	// Assignment operator
	this->WindowName	= other.WindowName;

	this->WindowWidth	= other.WindowWidth;
	this->WindowHeight	= other.WindowHeight;
	this->WindowPosX	= other.WindowPosX;
	this->WindowPosY	= other.WindowPosY;

	this->AllowReshape	= other.AllowReshape;
	this->FullScreen	= other.FullScreen;
}