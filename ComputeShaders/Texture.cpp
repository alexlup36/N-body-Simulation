#include "Texture.h"

#include <iostream>
#include <cassert>
#include "stb_image.h"
#include <SOIL2.h>

// ------------------------------------------------------------------------

Texture::Texture(int width, int height, 
	TextureType type, 
	bool bDepth, 
	GLenum glTextureTarget,
	GLint glTextureFilter)
{
	// Create and bind texture
	glGenTextures(1, &m_uiTexture);
	glBindTexture(glTextureTarget, m_uiTexture);
	glTexImage2D(glTextureTarget,
		0,
		bDepth ? GL_DEPTH_COMPONENT : GL_RGBA,
		width,
		height,
		0,
		bDepth ? GL_DEPTH_COMPONENT : GL_RGBA,
		GL_UNSIGNED_BYTE,
		NULL);

	// Set filtering
	glTexParameteri(glTextureTarget, GL_TEXTURE_MAG_FILTER, glTextureFilter);
	glTexParameteri(glTextureTarget, GL_TEXTURE_MIN_FILTER, glTextureFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Unbind texture
	glBindTexture(glTextureTarget, 0);
}

// ------------------------------------------------------------------------

Texture::Texture(int width, int height,
	GLint internalFormat,
	GLenum format,
	GLenum type,
	GLenum glTextureTarget,
	GLint glTextureFilter)
{
	// Create and bind texture
	glGenTextures(1, &m_uiTexture);
	glBindTexture(glTextureTarget, m_uiTexture);
	glTexImage2D(glTextureTarget,
		0,
		internalFormat,
		width,
		height,
		0,
		format,
		type,
		NULL);

	// Set filtering
	glTexParameteri(glTextureTarget, GL_TEXTURE_MAG_FILTER, glTextureFilter);
	glTexParameteri(glTextureTarget, GL_TEXTURE_MIN_FILTER, glTextureFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Unbind texture
	glBindTexture(glTextureTarget, 0);
}

// ------------------------------------------------------------------------

Texture::Texture(const std::string sFileName,
	TextureType type, 
	bool bImmutableStorage, 
	bool bEnableMipmaps,
	GLenum glTextureTarget,
	GLint glTextureFilter)
{
	// --------------------------------------------------------------------------
	// Load texture data from file

	int uiWidth, uiHeight, uiComponents;

	// Get the texture data from the file

	// Using soil
	unsigned char* sImageData = SOIL_load_image( sFileName.c_str(), &uiWidth, &uiHeight, &uiComponents, 4);

	if ( sImageData == NULL )
	{
		std::cout << "Texture loading failed " << sFileName << std::endl;
	}
	else
	{
		std::cout << "Texture data loaded successfully " << sFileName << std::endl;
	}

	// --------------------------------------------------------------------------

	// Create the texture handle
	glGenTextures( 1, &m_uiTexture );
	// Bind the current texture to the texture2D target
	glBindTexture( GL_TEXTURE_2D, m_uiTexture );

	// --------------------------------------------------------------------------

	// Set texture parameters
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// --------------------------------------------------------------------------

	switch (type)
	{
	case TextureType::Diffuse:
		m_bSRGB = true;
		break;
	case TextureType::Normal:
		m_bSRGB = false;
		break;
	case TextureType::Specular:
		m_bSRGB = false;
		break;
	case TextureType::Displacement:
		m_bSRGB = false;
	default:
		break;
	}

	// Allocate memory for the texture
	if (m_bSRGB)
	{
		// Mutable storage - Set texture data - convert colors to linear space so we can apply color correction
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, uiWidth, uiHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, sImageData);
	}
	else
	{
		if (bImmutableStorage)
		{
			// Immutable storage allocation
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, uiWidth, uiHeight);
			// Copy texture data
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, uiWidth, uiHeight, GL_RGBA, GL_UNSIGNED_BYTE, sImageData);
		}
		else
		{
			// Mutable storage - Set texture data
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, uiWidth, uiHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, sImageData);
		}
	}

	// --------------------------------------------------------------------------

	// Enable mip-maps
	if ( bEnableMipmaps == true )
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// --------------------------------------------------------------------------

	// Delete texture data
	if (sImageData != nullptr)
	{
		SOIL_free_image_data(sImageData);
		sImageData = nullptr;
	}

	// --------------------------------------------------------------------------
		
	// Unbind the current texture
	glBindTexture( GL_TEXTURE_2D, 0 );
}

// ------------------------------------------------------------------------

Texture::~Texture()
{
	glDeleteTextures( 1, &m_uiTexture );
}

// ------------------------------------------------------------------------

void Texture::Bind(unsigned int unit, GLuint program)
{
	assert( unit >= 0 && unit <= 32 );

	// Set the texture unit
	glActiveTexture( GLenum(GL_TEXTURE0 + unit) );

	// Bind the texture
	glBindTexture( GL_TEXTURE_2D, m_uiTexture );

	switch (unit)
	{
	case 0:
	{
		// Bind the diffuse sampler
		int location = glGetUniformLocation(program, "diffuseSampler");

		glUniform1i(location, unit);
		break;
	}
	case 1:
	{
		// Bind the normal sampler
		int location = glGetUniformLocation(program, "normalSampler");

		glUniform1i(location, unit);
		break;
	}
	case 2:
	{
		// Bind the displacement map sampler
		int location = glGetUniformLocation(program, "displacementSampler");

		glUniform1i(location, unit);
		break;
	}
	case 3:
	{
		// Bind the specular map sampler
		int location = glGetUniformLocation(program, "specularSampler");

		glUniform1i(location, unit);
		break;
	}
			
	default:
		break;
	}
}

// ------------------------------------------------------------------------

void Texture::BindImage(unsigned int unit, GLuint program)
{
	assert(unit >= 0 && unit <= 32);

	// Set the texture unit
	glActiveTexture(GLenum(GL_TEXTURE0 + unit));

	// Bind a level of the texture to image unit 0
	glBindImageTexture(0, m_uiTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	int location = glGetUniformLocation(program, "diffuseSampler");
	glUniform1i(location, unit);
}

// ------------------------------------------------------------------------

GLuint Texture::GetHandler()
{
	return m_uiTexture;
}

// ------------------------------------------------------------------------