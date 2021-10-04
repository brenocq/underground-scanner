#ifndef __SHADER
#define __SHADER
#include "glad/glad.h"
#include <filesystem>
namespace fs = std::filesystem;

class Shader
{
public:
	Shader(fs::path vertShader, fs::path fragShader);
	~Shader();

	void bind();
	void unbind();

private:
	unsigned compile(fs::path file, GLenum shaderType);
	void link(unsigned vertId, unsigned fragId);

	int _id;
};

#endif
