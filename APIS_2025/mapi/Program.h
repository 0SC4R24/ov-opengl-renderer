#pragma once

#include "common.h"
#include "Shader.h"

namespace old
{
	class Program
	{
	private:
		std::vector<std::string> shaderList;
		unsigned int programID;
		std::map<std::string, unsigned int> varList;
		bool linked = false;
	public:
		Program() { this->programID = -1; }
		void addShader(std::string fileName) { this->shaderList.push_back(fileName); }
		void linkProgram();
		void readVarList();
		void activate() { glUseProgram(programID); }

		void setAttributeMetaData(std::string attribName, GLint size, GLenum type, 
			GLboolean normalized, GLsizei stride, const GLvoid* pointer);
		void setMVP(glm::mat4 m);
	};
};