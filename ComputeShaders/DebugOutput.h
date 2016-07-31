#ifndef DEBUGOUTPUT_H
#define DEBUGOUTPUT_H

#include <SDL.h>
#include <GL\glew.h>
#include <assert.h>
#include <iostream>

#include "Common.h"

class DebugOutput
{
public:
	DebugOutput() {}
	~DebugOutput() {}

	static void __stdcall debugOutput(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* msg,
		const void* data)
	{
		printf("\n----------------------------Debug output----------------------------\n");
		printf("Source: %s\n", getStringForSource(source).c_str());
		printf("Type: %s\n", getStringForType(type).c_str());
		printf("Severity: %s\n", getStringForSeverity(severity).c_str());
		printf("Debug call: %s\n", msg);
		printf("\n----------------------------------------------------------------------");
	}

private:

	static std::string getStringForSource(GLenum source)
	{
		switch (source)
		{
			case GL_DEBUG_SOURCE_API:
				return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				return "Window system";
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				return "Shader compiler";
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				return "Third party";
			case GL_DEBUG_SOURCE_APPLICATION:
				return "Application";
			case GL_DEBUG_SOURCE_OTHER:
				return "Other";
			default:
				assert(false);
				return "";
		}
	}

	static std::string getStringForType(GLenum type)
	{
		switch (type)
		{
			case GL_DEBUG_TYPE_ERROR:
				return "Error";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				return "Deprecated behavior";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				return "Undefined behavior";
			case GL_DEBUG_TYPE_PORTABILITY:
				return "Portability issue";
			case GL_DEBUG_TYPE_PERFORMANCE:
				return "Performance issue";
			case GL_DEBUG_TYPE_MARKER:
				return "Stream annotation";
			case GL_DEBUG_TYPE_OTHER_ARB:
				return "Other";
			default:
				assert(false);
				return "";
		}
	}

	static std::string getStringForSeverity(GLenum severity)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:
				return "High";
			case GL_DEBUG_SEVERITY_MEDIUM:
				return "Medium";
			case GL_DEBUG_SEVERITY_LOW:
				return "Low";
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				return "Notification";
			default:
				assert(false);
				return("");
		}
	}
};

#endif // DEBUGOUTPUT_H