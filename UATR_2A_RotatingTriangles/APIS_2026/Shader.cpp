#include "Shader.h"

Shader::Shader(std::string fileName)
{
	char* code = nullptr;
	FILE* f = fopen(fileName.c_str(), "rb");

	if (!f)
	{
		std::cerr << "[ERROR] " << fileName << " file not found\n";
		return;
	}

	fseek(f, 0, SEEK_END);
	int fileSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	code = new char[fileSize];
	fread(code, fileSize, 1, f);
	fclose(f);
	
	for (int i = 0; i < fileSize; i++)
	{
		std::cout << code[i];
	}

	if (fileName.ends_with(".vert")) this->shaderType = GL_VERTEX_SHADER;
	else if (fileName.ends_with(".frag")) this->shaderType = GL_FRAGMENT_SHADER;

	this->shaderID = glCreateShader(this->shaderType);
	glShaderSource(this->shaderID, 1, &code, &fileSize);
	glCompileShader(this->shaderID);

	GLint retCode;
	char errorLog[1024];
	GLint fragment_compiled;
	glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &fragment_compiled);

	if (fragment_compiled != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(this->shaderID, 1024, &log_length, message);
		std::cout << "[ERROR] " << fileName << "\n" << message << "\n\n";
	}
	else
	{
		compiled = true;
	}

	free(code);
}
