#include "shader.h"
#include <vector>
#include <iostream>

namespace bengine
{
	namespace graphics
	{
		Shader::Shader(const char * vertPath, const char * fragPath) :
			_vertPath(vertPath), _fragPath(fragPath)
		{
			_shaderId = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(_shaderId);
		}

		void Shader::enable() const
		{
			glUseProgram(_shaderId);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSourceString = read_file(_vertPath);
			std::string fragSourceString = read_file(_fragPath);
				
			const char * vertSource = vertSourceString.c_str();
			const char * fragSource = fragSourceString.c_str();

			GLint result;

			glShaderSource(vertex, 1, &vertSource, nullptr);
			glCompileShader(vertex);

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader." << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSource, nullptr);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader." << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		GLint Shader::getUniformLocation(const GLchar * name)
		{
			return glGetUniformLocation(_shaderId, name);
		}

		void Shader::setUniform1f(const GLchar * name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform1i(const GLchar * name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const GLchar * name, const maths::Vector2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3f(const GLchar * name, const maths::Vector3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const GLchar * name, const maths::Vector4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4(const GLchar * name, const maths::Matrix4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}
	}
}
