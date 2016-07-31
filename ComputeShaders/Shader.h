#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TransformComponent.h"


class Shader
{
public:
	enum ShaderType
	{
		Vertex = 0,
		Fragment,
		Compute,

		ShaderTypeCount,
	};

public:
	Shader();
	~Shader(void);

	void AddSource(ShaderType shaderType, const char* sourceCodePath);

	// Compile shaders
	GLuint SetupShaders();

	//void Update();

	// Enable the use of the shader
	//void Enable() const;
	//void Disable() const;

	// Get the uniform variable location
	//GLuint GetUniformLocation(const char* uniformVarName);

	// Return the program ID
	GLuint ProgramID() const;

	// Get/Set transformation
	//Transform* GetTransform();
	//void SetTransform(Transform* pTransform);

	//bool operator<( const Shader& other) const;

private:
	enum Uniforms
	{
		keMODELMATRIX,
		keVIEWMATRIX,
		kePROJECTIONMATRIX,
		keNORMALMATRIX,
		keEYEPOSW,

		keNUM_UNIFORMS,
	};

	// Flags to signal what types of shaders are attached
	bool m_bShader[ShaderType::ShaderTypeCount];

	// Vertex shader and fragment shader
	GLuint _VertexShaderID;
	GLuint _FragmentShaderID;
	GLuint _ComputeShaderID;

	// Shader program
	GLuint _ShaderProgramID;

	//GLuint m_uiUniforms[ keNUM_UNIFORMS ];

	// File paths for both the vertex shader and fragment shader
	char _vertexShaderPath[100];
	char _fragmentShaderPath[100];
	char _computeShaderPath[100];

	// Transform reference
	//Transform* m_pTransform;

	// Methods ----------------------------------------------------------------

	// Read shader code from file to string
	int ReadShaderFromFile(std::string& shaderCode, const char* shaderPath);
	// Compile and check the shader
	void CompileShader(GLuint shaderID, std::string& shaderCode, const char* shaderPath);
	// Create the program
	void CreateProgram();

	inline const bool IsShaderType(ShaderType shaderType) const
	{
		if (shaderType >= 0 && shaderType < ShaderType::ShaderTypeCount)
		{
			return m_bShader[shaderType];
		}
		return false;
	}
	inline const void SetShaderType(ShaderType shaderType)
	{
		if (shaderType >= 0 && shaderType < ShaderType::ShaderTypeCount)
		{
			m_bShader[shaderType] = 1;
		}
	}		
};


#endif // __SHADER_H__