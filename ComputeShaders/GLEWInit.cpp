#include "GLEWInit.h"


bool GLEWInit::Init()
{
	bool bSuccess = true;

	glewExperimental = true;

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s \n", glewGetErrorString(glewError));
		bSuccess = false;
	}

	/*if (glewIsSupported("GL_VERSION_4_5"))
	{
		printf("OpenGL version 4.5 is supported.\n");
	}
	else
	{
		printf("OpenGL version 4.5 is not supported.\n");
	}*/

	return bSuccess;
}
