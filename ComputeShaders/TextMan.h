#ifndef __TEXTMAN_H__
#define __TEXTMAN_H__

#include "Shader.h"
#include "ShaderMan.h"
#include "Texture.h"

class TextMan
{
public:
	TextMan(void);
	~TextMan(void);

	void Initialize(ShaderMan* shaderMan, const char* sFontTexturePath);
	void PrintText(ShaderMan* shaderMan, const char* sText, int x, int y, int size);

private:
	Texture* m_pTextTexture;

	GLuint m_Text2DVertexBufferID;
	GLuint m_Text2DUVBufferID;

	GLuint m_VertexArrayObject;
};

#endif __TEXTMAN_H__