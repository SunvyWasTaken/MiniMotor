#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Sunset
{
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

		GLint isCompiled = 0;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertex, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertex);

			LOG("{}", infoLog.data());
			assert(false, "Vertex shader compilation failure!");
			return;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		isCompiled = 0;
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragment, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragment);

			LOG("{}", infoLog.data());
			assert(false, "Vertex shader compilation failure!");
			return;
		}

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
			LOG("ERROR::SHADER::PROGRAM::LINKING_FAILED\n {}", infoLog);
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	ShaderOGL::~ShaderOGL()
	{
		glDeleteProgram(_id);
	}

	void ShaderOGL::Use()
	{
		glUseProgram(_id);
	}

	void ShaderOGL::Set1I(const std::string& target, const int value)
	{
		glUniform1i(glGetUniformLocation(_id, target.c_str()), value);
	}

	void ShaderOGL::Set1F(const std::string& target, const float value)
	{
		glUniform1f(glGetUniformLocation(_id, target.c_str()), value);
	}

	void ShaderOGL::SetVec3F(const std::string& target, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(_id, target.c_str()), 1, glm::value_ptr(value));
	}

	void ShaderOGL::SetMatrice4(const std::string& target, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(_id, target.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
}
