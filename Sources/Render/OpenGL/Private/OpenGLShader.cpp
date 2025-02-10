#include "OpenGLShader.h"

#include <glad/glad.h>

ShaderOGL::ShaderOGL(const std::string& vertPath, const std::string& fragPath)
	: _id(0)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.open(vertPath);
	fShaderFile.open(fragPath);
	std::stringstream vShaderStream, fShaderStream;
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();
	vShaderFile.close();
	fShaderFile.close();
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	_id = glCreateProgram();

	glAttachShader(_id, vertex);
	glAttachShader(_id, fragment);
	glLinkProgram(_id);
	int success;
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

ShaderOGL::~ShaderOGL()
{
	glDeleteProgram(_id);
	std::cerr << "Shader detruit" << std::endl;
}

void ShaderOGL::Use()
{
	glUseProgram(_id);
}
