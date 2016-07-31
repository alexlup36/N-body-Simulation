#include "Shader.h"

#include "gtc/matrix_inverse.hpp"


Shader::Shader()
{
	// Default shader setup - no shaders attached
	for (int i = 0; i < ShaderType::ShaderTypeCount; ++i)
	{
		m_bShader[i] = false;
	}
}

void Shader::AddSource(ShaderType shaderType, const char* sourceCodePath)
{
	switch (shaderType)
	{
		case ShaderType::Vertex:
		{
			if (IsShaderType(ShaderType::Compute) == false)
			{
				// If the program doesn't have a compute shader attached we can make it vertex shader
				SetShaderType(shaderType);

				if (sourceCodePath != NULL)
				{
					strcpy_s(_vertexShaderPath, strlen(sourceCodePath) + 1, sourceCodePath);

					// Create the fragment shaders
					_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
				}
			}

			break;
		}
		case ShaderType::Fragment:
		{
			if (IsShaderType(ShaderType::Compute) == false)
			{
				// If the program doesn't have a compute shader attached we can make it fragment shader
				SetShaderType(shaderType);

				if (sourceCodePath != NULL)
				{
					strcpy_s(_fragmentShaderPath, strlen(sourceCodePath) + 1, sourceCodePath);

					// Create the fragment shaders
					_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
				}
			}

			break;
		}
		case ShaderType::Compute:
		{
			if (!(IsShaderType(ShaderType::Vertex) || IsShaderType(ShaderType::Fragment)))
			{
				// If the program doesn't have a vertex or a fragment shader attached we can make it compute shader
				SetShaderType(shaderType);

				if (sourceCodePath != NULL)
				{
					strcpy_s(_computeShaderPath, strlen(sourceCodePath) + 1, sourceCodePath);

					// Create the fragment shaders
					_ComputeShaderID = glCreateShader(GL_COMPUTE_SHADER);
				}
			}

			break;
		}
	}
}

Shader::~Shader(void)
{
	glDetachShader(_ShaderProgramID, _VertexShaderID);
	glDetachShader(_ShaderProgramID, _FragmentShaderID);
	glDetachShader(_ShaderProgramID, _ComputeShaderID);

	glDeleteProgram(_ShaderProgramID);

	glDeleteShader(_VertexShaderID);
	glDeleteShader(_FragmentShaderID);
	glDeleteShader(_ComputeShaderID);
}

//void Shader::Update()
//{ 
	//// Get the active camera
	//Camera* pActiveCamera = CameraMan::Instance().GetActiveCamera();

	//// Set the model matrix for the shaders which have one
	//if (m_pTransform != NULL)
	//{
	//	// Set the model matrix
	//	if (m_uiUniforms[keMODELMATRIX] != -1)
	//	{
	//		// Calculate the model matrix
	//		glm::mat4 modelMat = m_pTransform->GetModel();

	//		glUniformMatrix4fv(m_uiUniforms[keMODELMATRIX], 1, GL_FALSE, &modelMat[0][0]);
	//	}

	//	// Set the view matrix
	//	if (m_uiUniforms[keVIEWMATRIX] != -1)
	//	{
	//		// Get the projection matrix
	//		glm::mat4 viewMat = pActiveCamera->ViewMatrix();

	//		glUniformMatrix4fv(m_uiUniforms[keVIEWMATRIX], 1, GL_FALSE, &viewMat[0][0]);
	//	}

	//	// Set the projection matrix
	//	if (m_uiUniforms[kePROJECTIONMATRIX] != -1)
	//	{
	//		// Get the projection matrix
	//		glm::mat4 projectionMat = pActiveCamera->ProjectionMatrix();

	//		glUniformMatrix4fv(m_uiUniforms[kePROJECTIONMATRIX], 1, GL_FALSE, &projectionMat[0][0]);
	//	}

	//	// Set the normal matrix
	//	if (m_uiUniforms[keNORMALMATRIX] != -1)
	//	{
	//		// Get the model matrix to transform normals to world space
	//		glm::mat4 mMat = m_pTransform->GetModel();
	//		// Calculate the inverse transpose model matrix
	//		glm::mat4 normalMatrix = glm::transpose(glm::inverse(mMat));

	//		// Send the transpose inverse of the model view matrix
	//		glUniformMatrix4fv(m_uiUniforms[keNORMALMATRIX], 1, GL_FALSE, &normalMatrix[0][0]);
	//	}

	//	// Set the eye pos
	//	if (m_uiUniforms[keEYEPOSW] != -1)
	//	{
	//		glUniform3fv(m_uiUniforms[keEYEPOSW], 1, &pActiveCamera->GetCameraPosition()[0]);
	//	}
	//}
//}

//void Shader::Enable() const
//{
//	glUseProgram(_ShaderProgramID);
//}
//
//void Shader::Disable() const
//{
//	glUseProgram(0);
//}
//
// Get the program ID
GLuint Shader::ProgramID() const
{
	return _ShaderProgramID;
}
//
//Transform* Shader::GetTransform()
//{
//	return m_pTransform;
//}
//
//void Shader::SetTransform(Transform* pTransform)
//{
//	m_pTransform = pTransform;
//}

int Shader::ReadShaderFromFile(std::string& shaderCode, const char* shaderPath)
{
	std::ifstream ShaderStream(shaderPath, std::ios::in);

	if (ShaderStream.is_open())
	{
		std::string Line = "";

		while (getline(ShaderStream, Line))
		{
			shaderCode += "\n" + Line;
		}

		ShaderStream.close();
	} 
	else
	{
		std::cout << "Failed to open %s." << shaderPath << std::endl;
		return 0;
	}

	return 1;
}

void Shader::CompileShader(GLuint shaderID, std::string& shaderCode, const char* shaderPath)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Shader
	std::cout << "Compiling shader: " << shaderPath << "." << std::endl;
	char const* SourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &SourcePointer , NULL);
	glCompileShader(shaderID);

	// Check Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		//std::cout<<ShaderErrorMessage[0]<<std::endl;
		printf("%s\n", &ShaderErrorMessage[0]);
	}
}

void Shader::CreateProgram()
{
	check_gl_error();

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Link the program
	std::cout << "Linking program" << std::endl;
	_ShaderProgramID = glCreateProgram();

	check_gl_error();

	if (IsShaderType(ShaderType::Vertex))
	{
		glAttachShader(_ShaderProgramID, _VertexShaderID);
		check_gl_error();
	}
	if (IsShaderType(ShaderType::Fragment))
	{
		glAttachShader(_ShaderProgramID, _FragmentShaderID);
		check_gl_error();
	}
	if (IsShaderType(ShaderType::Compute))
	{
		glAttachShader(_ShaderProgramID, _ComputeShaderID);
		check_gl_error();
	}
	
	glLinkProgram(_ShaderProgramID);
	check_gl_error();

	// Check the program
	glGetProgramiv(_ShaderProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(_ShaderProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(_ShaderProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
}

GLuint Shader::SetupShaders()
{
	check_gl_error();

	if (IsShaderType(ShaderType::Vertex) == true)
	{
		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		if (ReadShaderFromFile(VertexShaderCode, _vertexShaderPath) == 1)
		{
			// Compile Vertex Shader
			CompileShader(_VertexShaderID, VertexShaderCode, _vertexShaderPath);
		}
		else
		{
			std::cout << "Failed to read vertex shader." << std::endl;
		}
	}

	check_gl_error();

	if (IsShaderType(ShaderType::Fragment) == true)
	{
		// Read the Fragment Shader code from the file
		std::string FragmentShaderCode;
		if (ReadShaderFromFile(FragmentShaderCode, _fragmentShaderPath) == 1)
		{
			// Compile Fragment Shader
			CompileShader(_FragmentShaderID, FragmentShaderCode, _fragmentShaderPath);
		}
		else
		{
			std::cout << "Failed to read fragment shader." << std::endl;
		}
	}

	check_gl_error();

	if (IsShaderType(ShaderType::Compute) == true)
	{
		// Read the Compute Shader code from the file
		std::string ComputeShaderCode;
		if (ReadShaderFromFile(ComputeShaderCode, _computeShaderPath) == 1)
		{
			// Compile Fragment Shader
			CompileShader(_ComputeShaderID, ComputeShaderCode, _computeShaderPath);
		}
		else
		{
			std::cout << "Failed to read fragment shader." << std::endl;
		}
	}

	check_gl_error();

	// Link the program
	CreateProgram();

	check_gl_error();
		
	// Get the uniforms
	/*m_uiUniforms[keMODELMATRIX]			= GetUniformLocation("mMatrix");
	m_uiUniforms[keVIEWMATRIX]			= GetUniformLocation("vMatrix");
	m_uiUniforms[kePROJECTIONMATRIX]	= GetUniformLocation("pMatrix");
	m_uiUniforms[keNORMALMATRIX]		= GetUniformLocation("nMatrix");
	m_uiUniforms[keEYEPOSW]				= GetUniformLocation("eyePosW");*/

	return _ShaderProgramID;
}

//GLuint Shader::GetUniformLocation(const char* uniformVarName)
//{
//	GLint location = glGetUniformLocation(_ShaderProgramID, uniformVarName);
//
//	return location;
//}
//
//bool Shader::operator<( const Shader& other) const
//{
//	return 0;
//}