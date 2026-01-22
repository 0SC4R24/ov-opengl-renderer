#pragma once

#include "common.h"

namespace old
{
	class Shader
	{
	public:
		unsigned int shaderID;
		unsigned int shaderType;
		bool compiled = false;
	
		Shader(std::string fileName);
	};
};