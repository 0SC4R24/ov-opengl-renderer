#include "GLSLMaterial.h"

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
	// TODO: Metodo virtual que inicializara adecuadamente las variables del
	//       RenderProgram a partir de los objetos
}