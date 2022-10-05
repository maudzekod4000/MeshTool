#include "ShaderProgram.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void ShaderProgram::init()
{
	shaderTypeToShaderId.clear();
	shaderProgram = glCreateProgram();
	this->isSuccess = 1;
}

void ShaderProgram::attachVertexShader(const std::string& shaderPath)
{
	attachShader(GL_VERTEX_SHADER, shaderLoader.load(shaderPath).data());
}

void ShaderProgram::attachFragmentShader(const std::string& shaderName)
{
	attachShader(GL_FRAGMENT_SHADER, shaderLoader.load(shaderName).data());
}

void ShaderProgram::attachShader(unsigned int shaderType, const char* shaderSourceCode) {
	shaderTypeToShaderId[shaderType] = glCreateShader(shaderType);

	glShaderSource(shaderTypeToShaderId[shaderType], 1, &shaderSourceCode, NULL);
	glCompileShader(shaderTypeToShaderId[shaderType]);
	glGetShaderiv(shaderTypeToShaderId[shaderType], GL_COMPILE_STATUS, &isSuccess);

	if (!isSuccess) {
		char infoLog[512];
		glGetShaderInfoLog(shaderTypeToShaderId[shaderType], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glAttachShader(shaderProgram, shaderTypeToShaderId[shaderType]);
}

int ShaderProgram::findLocation(const std::string& uniformVarName) const
{
	return glGetUniformLocation(shaderProgram, uniformVarName.c_str());
}

void ShaderProgram::link()
{
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isSuccess);

	if (!isSuccess)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	for (auto const& pair : shaderTypeToShaderId) {
		glDeleteShader(pair.second);
	}
}

void ShaderProgram::use()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::setUniformMat4(const std::string& uniformVarName, const glm::mat4& value) const
{
	glUniformMatrix4fv(findLocation(uniformVarName), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniformVec4(const std::string& uniformVarName, const glm::vec4& value) const
{
	glUniform4f(findLocation(uniformVarName), value.x, value.y, value.z, value.a);
}

void ShaderProgram::setUniformVec3(const std::string& uniformVarName, const glm::vec3& value) const
{
	glUniform3f(findLocation(uniformVarName), value.x, value.y, value.z);
}

void ShaderProgram::setUniformF(const std::string& uniformVarName, float value) const
{
	glUniform1f(findLocation(uniformVarName), value);
}

void ShaderProgram::setInt(const std::string& uniformVarName, unsigned int value) const
{
	int loc = findLocation(uniformVarName);
	glUniform1i(findLocation(uniformVarName), value);
}
