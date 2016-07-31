#include "ShaderMan.h"

#include "Common.h"

std::map<std::string, GLuint> ShaderMan::m_pProgramList;

ShaderMan::ShaderMan()
{
}

// Override 
ShaderMan::~ShaderMan(void) 
{
	size_t shaderCount = m_pShaderList.size();

	for (size_t i = 0; i < shaderCount; ++i)
	{
		if (m_pShaderList[i] != nullptr)
		{
			delete m_pShaderList[i];
			m_pShaderList[i] = nullptr;
		}
	}

	m_pShaderList.clear();
}

void ShaderMan::AddShader(const std::string shaderName,
	Shader* newShader)
{
	check_gl_error();

	// Add new shader to the shader list
	m_pShaderList.push_back(newShader);

	// Add shader program to the map
	if (m_pProgramList.find(shaderName) == m_pProgramList.end())
	{
		// The specified shaderName could not be found
		m_pProgramList[shaderName] = newShader->ProgramID();
	}	
}

const GLuint ShaderMan::GetShader(const std::string & shaderName)
{
	if (m_pProgramList.find(shaderName) != m_pProgramList.end())
	{
		return m_pProgramList[shaderName];
	}
	else
	{
		printf("Unable to find shader %s.\n", shaderName.c_str());
		return 0;
	}
}
