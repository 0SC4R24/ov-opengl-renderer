#pragma once

#include "mapi/common.h"

class Shader
{
public:
	unsigned int shaderID;
	unsigned int shaderType;
	bool compiled = false;
	
	Shader(std::string fileName);
};

