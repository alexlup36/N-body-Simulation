#ifndef __COMMON_H__
#define __COMMON_H__

#define GLM_FORCE_RADIANS 1
#define X_FULLSCREEN 0

// Define resolutions for window and full screen modes
#if X_FULLSCREEN
	constexpr int WINDOW_WIDTH = 1920;
	constexpr int WINDOW_HEIGHT = 1080;
#else
	constexpr int WINDOW_WIDTH = 1600;
	constexpr int WINDOW_HEIGHT = 900;
#endif // FULL_SCREEN

// Includes ------------------------------------------------------------------------------

#include <stdio.h>
#include <GL/glew.h>
#include <string>

// ---------------------------------------------------------------------------------------

void Log( const char* szMessage );
void Log( const char* szTag, const char* szMessage );
void GLClearErrors();
void GLErrorCheck( const char* szMessage = NULL);

void checkGLError(const char* file, int line);
#define check_gl_error() checkGLError(__FILE__, __LINE__)

#endif // __COMMON_H__