#include "GLSLMaterial.h"
#include "System.h"

void GLSLMaterial::loadPrograms(std::vector<std::string> shaderFileNames)
{
	for (auto& s : shaderFileNames)
	{
		m_program->addProgram(s);
	}

	m_program->linkProgram();
}

void GLSLMaterial::prepare()
{
	m_program->use();
	m_program->setMatrix("M", System::getModelMatrix());
}