#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Common.h"
#include <string>

enum class TextureType
{
	Diffuse,
	Normal,
	Specular,
	Displacement,
};

class Texture
{
public:
		
	// Create empty texture
	Texture(int width, int height, 
		TextureType type,
		bool bDepth, 
		GLenum glTextureTarget = GL_TEXTURE_2D,
		GLint glTextureFilter = GL_LINEAR);

	// Create empty texture
	Texture(int width, int height,
		GLint internalFormat		= GL_R32F,
		GLenum format				= GL_RED,
		GLenum type					= GL_FLOAT,
		GLenum glTextureTarget		= GL_TEXTURE_2D,
		GLint glTextureFilter		= GL_LINEAR);

	// Create texture from file
	Texture(const std::string sFileName, 
		TextureType type, 
		bool bImmutableStorage, 
		bool bEnableMipmaps = false,
		GLenum glTextureTarget = GL_TEXTURE_2D,
		GLint glTextureFilter = GL_LINEAR);

	virtual ~Texture();

	void Bind(unsigned int unit, GLuint program);
	void BindImage(unsigned int unit, GLuint program);
	GLuint GetHandler();

protected:

private:
	Texture( const Texture& other ) {}
	void operator=( const Texture& other ) {}

	GLuint m_uiTexture;
	bool m_bSRGB;
};

#endif // __TEXTURE_H__