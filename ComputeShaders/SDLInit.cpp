#include "SDLInit.h"

#include "GLEWInit.h"

// ------------------------------------------------------------------------

// OpenGL context
SDL_GLContext SDLInit::m_SDLContext = nullptr;
// Window
SDL_Window* SDLInit::m_pWindow = nullptr;

// ------------------------------------------------------------------------

bool SDLInit::Init(const ContextInfo& contextInfo,
	const WindowInfo& windowInfo,
	const FrameBufferInfo& frameBufferInfo)
{
	// Initialize SDL
	bool bSuccess = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL error %s\n", SDL_GetError());
		bSuccess = false;
	}
	else
	{
		// ------------------------------------------------------------------------
		// Set OpenGL version request
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, contextInfo.MajorVersion);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, contextInfo.MinorVersion);
		if (contextInfo.Core)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		}
		else
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		}
		
		// Request double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// Multisample antialiasing
		if (frameBufferInfo.EnableMSAA)
		{
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, frameBufferInfo.MSAASampleCount);
		}
		else
		{
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
		}

		// Request SRGB capable visuals
		if (frameBufferInfo.EnableSRGB)
		{
			SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);
		}
		else
		{
			SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 0);
		}

#ifdef _DEBUG

		glEnable(GL_DEBUG_OUTPUT);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

		if (GL_KHR_debug)
		{
			int x = 0;
		}

#endif // _DEBUG

		// ------------------------------------------------------------------------
		// Create SDL window
		// Default window flags
		Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;

		// If full screen set, modify the window flags
		if (windowInfo.FullScreen)
		{
			windowFlags |= SDL_WINDOW_FULLSCREEN;
		}
		if (windowInfo.AllowReshape)
		{
			windowFlags |= SDL_WINDOW_RESIZABLE;
		}

		m_pWindow = SDL_CreateWindow(windowInfo.WindowName.c_str(),
			windowInfo.WindowPosX,
			windowInfo.WindowPosY,
			windowInfo.WindowWidth,
			windowInfo.WindowHeight,
			windowFlags);

		if (m_pWindow == NULL)
		{
			printf("SDL windows could not be created! SDL error %s\n", SDL_GetError());
			bSuccess = false;
		}
		else
		{
			// ------------------------------------------------------------------------
			// Create GL context
			m_SDLContext = SDL_GL_CreateContext(m_pWindow);
			if (m_SDLContext == NULL)
			{
				printf("OpenGL context could not be created! SDL error: %s \n", SDL_GetError());
				bSuccess = false;
			}
			else
			{
				// Initialize GLEW
				bSuccess = GLEWInit::Init();

				// Use vsync
				if (frameBufferInfo.EnableVSync)
				{
					if (SDL_GL_SetSwapInterval(1) < 0)
					{
						printf("Warning: Unable to set VSync! SDL error: %s \n", SDL_GetError());

						// VSync not supported => set immediate swap interval
						SDL_GL_SetSwapInterval(0);
					}
				}
				else
				{
					// No vsync => immediate swap
					SDL_GL_SetSwapInterval(0);
				}
			}
		}
	}

	return bSuccess;
}

SDLInit::~SDLInit()
{
	// Deallocate program
	glUseProgram(0);

	// Destroy SDL context
	SDL_GL_DeleteContext(m_SDLContext);

	// Destroy window
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;

	// Quit SDL
	SDL_Quit();
}
