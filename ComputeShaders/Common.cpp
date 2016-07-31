#include "Common.h"

void Log( const char* szMessage )
{
	printf("%s\n", szMessage);
}

void Log( const char* szTag, const char* szMessage )
{ 
	printf("%s : %s\n", szTag, szMessage);
}

void GLErrorCheck(const char* szMessage /*=NULL*/)
{
	GLenum checkResult = glGetError();

	if (checkResult != GL_NO_ERROR)
	{
		if (szMessage != NULL)
		{
			printf("%s - ", szMessage);
		}
		
		switch ( checkResult )
		{
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			printf("ERROR: Invalid enum.\n");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			printf("ERROR: Invalid framebuffer operation.\n");
			break;
		case GL_INVALID_INDEX:
			printf("ERROR: Invalid index.\n");
			break;
		case GL_INVALID_OPERATION:
			printf("ERROR: Invalid operation.\n");
			break;
		case GL_INVALID_VALUE:
			printf("ERROR: Invalid value.\n");
			break;
		case GL_OUT_OF_MEMORY:
			printf("ERROR: Out of memory.\n");
			break;
		case GL_STACK_OVERFLOW:
			printf("ERROR: Stack overflow.\n");
			break;
		case GL_STACK_UNDERFLOW:
			printf("ERROR: Stack underflow.\n");
			break;
		default:
			break;
		}

		
	}
}

void GLClearErrors()
{
	glGetError();
}

void checkGLError(const char* file, int line)
{
	GLenum error(glGetError());

	while (error != GL_NO_ERROR)
	{
		std::string errorMessage;

		switch (error)
		{
			case GL_INVALID_OPERATION:
			{
				errorMessage = "INVALID_OPERATION";
				break;
			}
			case GL_INVALID_ENUM:
			{
				errorMessage = "INVALID_ENUM";
				break;
			}
			case GL_INVALID_VALUE:
			{
				errorMessage = "INVALID_VALUE";
				break;
			}
			case GL_INVALID_FRAMEBUFFER_OPERATION:
			{
				errorMessage = "INVALID_FRAMEBUFFER_OPERATION";
				break;
			}
			case GL_OUT_OF_MEMORY:
			{
				errorMessage = "OUT_OF_MEMORY";
				break;
			}
			case GL_STACK_UNDERFLOW:
			{
				errorMessage = "STACK_UNDERFLOW";
				break;
			}
			case GL_STACK_OVERFLOW: 
			{
				errorMessage = "STACK_OVERFLOW";
				break;
			}
		}

		printf("GL_%s - File %s : line %d\n", errorMessage.c_str(), file, line);

		error = glGetError();
	}
}