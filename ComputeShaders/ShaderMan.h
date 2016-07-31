#ifndef __SHADERMAN_H__
#define __SHADERMAN_H__

#include "Common.h"
#include "Shader.h"

#include <map>


class ShaderMan
{
public:	
	ShaderMan();	
	~ShaderMan();

	void AddShader(const std::string shaderName, Shader* newShader);
	static const GLuint GetShader(const std::string& shaderName);

private:
	// ------------------------------------------------------
	static std::map<std::string, GLuint> m_pProgramList;

	std::vector<Shader*> m_pShaderList;
};

#endif // __SHADERMAN_H__