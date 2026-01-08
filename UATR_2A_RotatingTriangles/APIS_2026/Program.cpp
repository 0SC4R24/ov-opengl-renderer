#include "Program.h"

void Program::linkProgram()
{
	this->programID = glCreateProgram();

	for (auto& c : this->shaderList)
	{
		Shader shader(c);

		if (shader.compiled)
		{
			glAttachShader(this->programID, shader.shaderID);
		}

	}
	
	glLinkProgram(this->programID);

	GLint program_linked;
	glGetProgramiv(this->programID, GL_LINK_STATUS, &program_linked);

	if (program_linked != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(this->programID, 1024, &log_length, message);
		std::cerr << "[ERROR] Failed linking program\n" << message << "\n\n";
	}
	else
	{
		linked = true;
	}

	readVarList();
}

void Program::readVarList()
{
	glUseProgram(this->programID);
	
	int numAttributes = 0;
	glGetProgramiv(this->programID, GL_ACTIVE_ATTRIBUTES, &numAttributes);

	for (int i = 0; i < numAttributes; i++)
	{
		char name[101];
		int size;
		unsigned int type;
		int length;

		glGetActiveAttrib(this->programID, (GLuint) i, 100, &length, &size, &type, name);
		
		int layout = glGetAttribLocation(this->programID, name);

		this->varList[std::string(name)] = layout;
	}

	int numUniforms = 0;
	glGetProgramiv(this->programID, GL_ACTIVE_UNIFORMS, &numUniforms);

	for (int i = 0; i < numUniforms; i++)
	{
		char name[101];
		int size;
		unsigned int type;
		int length;

		glGetActiveUniform(this->programID, (GLuint)i, 100, &length, &size, &type, name);

		int layout = glGetUniformLocation(this->programID, name);

		this->varList[std::string(name)] = layout;
	}
}

void Program::setAttributeMetaData(std::string attribName, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	if (varList.find(attribName) != varList.end())
	{
		glEnableVertexAttribArray(this->varList[attribName]);
		glVertexAttribPointer(this->varList[attribName], size, type, normalized, stride, pointer);
	}
	else
	{
		std::cerr << "[ERROR] " << attribName << " attribute not found\n";
	}
}

void Program::setMVP(glm::mat4 m)
{
	if (varList.find("MVP") != varList.end())
	{
		glUniformMatrix4fv(varList["MVP"], 1, false, &m[0][0]);
	}
	else
	{
		std::cerr << "[ERROR] MVP uniform not found\n";
	}
}
