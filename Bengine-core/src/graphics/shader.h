#pragma once

#include "../utils/fileutils.h"
#include "../maths/maths.h"
#include <GL/glew.h>

namespace bengine
{
	namespace graphics
	{
		class Shader
		{
		private:
			const char * _vertPath, *_fragPath;
			GLuint _shaderId;

			GLuint load();
			GLint getUniformLocation(const GLchar * name);

		public:
			Shader(const char * vertPath, const char * fragPath);
			~Shader();

			void setUniform1f(const GLchar * name, float value);
			void setUniform1i(const GLchar * name, int value);
			void setUniform2f(const GLchar * name, const maths::Vector2& vector);
			void setUniform3f(const GLchar * name, const maths::Vector3& vector);
			void setUniform4f(const GLchar * name, const maths::Vector4& vector);
			void setUniformMat4(const GLchar * name, const maths::Matrix4& matrix);

			void enable() const;
			void disable() const;
		};
	}
}
