#ifndef SDLINIT_H
#define SDLINIT_H

#include <SDL.h>
#include <stdio.h>

#include "Common.h"
#include "ContextInfo.h"
#include "WindowInfo.h"
#include "FrameBufferInfo.h"

class SDLInit
{
public:
	static bool Init(const ContextInfo& contextInfo,
		const WindowInfo& windowInfo,
		const FrameBufferInfo& frameBufferInfo);
	~SDLInit();

	inline static SDL_Window* GetWindow() { return m_pWindow; }

private:
	// OpenGL context
	static SDL_GLContext m_SDLContext;
	// Window
	static SDL_Window* m_pWindow;
};

#endif // SDLINIT_H