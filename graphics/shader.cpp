#include "graphics/shader.hpp"
#include <iostream>
#include <fstream>

Shader::Shader(fs::path vertShader, fs::path fragShader)
{
	unsigned vertId = compile(vertShader, GL_VERTEX_SHADER);
	unsigned fragId = compile(fragShader, GL_FRAGMENT_SHADER);
	link(vertId, fragId);
}

Shader::~Shader()
{
	glDeleteProgram(_id);
}

void Shader::bind()
{
	glUseProgram(_id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

unsigned Shader::compile(fs::path file, GLenum shaderType)
{
	unsigned id;

	// Create shader
	id = glCreateShader(shaderType);

	// Read file
	std::stringstream fileSS;
	std::ifstream infile(file);
	fileSS << infile.rdbuf();
	infile.close();

	// Compile
	std::string codeStr = fileSS.str();
	const char* code = codeStr.c_str();
	glShaderSource(id, 1, &code, NULL);
	glCompileShader(id);

	// Check errors
	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "Failed to compile shader " << file.string() << ". " << infoLog << std::endl;
	}

	return id;
}

void Shader::link(unsigned vertId, unsigned fragId)
{
	_id = glCreateProgram();

	// Attach shaders
	glAttachShader(_id, vertId);
	glAttachShader(_id, fragId);

	// Link shaders
	glLinkProgram(_id);

	// Check errors
	int success;
	char infoLog[512];
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(_id, 512, NULL, infoLog);
		std::cout << "[Shader] Failed to link shaders. " << infoLog << std::endl;
	}

	// Delete shaders
	glDeleteShader(vertId);
	glDeleteShader(fragId);
}
