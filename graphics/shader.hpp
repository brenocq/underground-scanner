#ifndef __SHADER
#define __SHADER
#include <glad/glad.h>
#include <filesystem>

#include <glm/glm.hpp>

namespace fs = std::filesystem;

class Shader
{
public:
	Shader(fs::path vertShader, fs::path fragShader);
	~Shader();

	void bind();
	void unbind();

	void setUniformV4(const char* uniformName, glm::vec4 value);
	void setUniformM4(const char* uniformName, glm::mat4 value);
private:
	unsigned compile(fs::path file, GLenum shaderType);
	void link(unsigned vertId, unsigned fragId);

	int _id;
};

#endif
