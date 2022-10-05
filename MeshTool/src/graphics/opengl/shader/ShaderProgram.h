#pragma once

#include <string>
#include <unordered_map>

#include "../../../models/TypeDefs.h"

#include "ShaderLoader.h"

/*
* A shader program is a configuration of vertex, fragment and optionally geometry shader.
* We can load the shaders into the program and link them.
* Later when we need to use/activate the shaders we call use(). That way we can toggle between shader sets.
*/
class ShaderProgram
{
public:
	void init();
	void attachVertexShader(const std::string& shaderName);
	void attachFragmentShader(const std::string& shaderName);
	void link();
	void use();
	void setUniformMat4(const std::string& uniformVarName, const glm::mat4& value) const;
	void setUniformVec4(const std::string& uniformVarName, const glm::vec4& value) const;
	void setUniformVec3(const std::string& uniformVarName, const glm::vec3& value) const;
	void setUniformF(const std::string& uniformVarName, float value) const;
	void setInt(const std::string& uniformVarName, unsigned int value) const;
private:
	ShaderLoader shaderLoader;
	unsigned int shaderProgram;
	std::unordered_map<unsigned int, unsigned int> shaderTypeToShaderId;
	int isSuccess;

	void attachShader(unsigned int shaderType, const char* shaderSourceCode);
	int findLocation(const std::string& uniformVarName) const;
};
