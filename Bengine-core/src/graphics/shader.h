#pragma once

#include "../utils/fileutils.h"
#include <GL/glew.h>

namespace bengine
{
	namespace graphics
	{
		class Shader
		{
		private:
			GLuint _shaderId;
			const char * _vertPath, * _fragPath;

			GLuint load();

		public:
			Shader(const char * vertPath, const char * fragPath);
			~Shader();

			void enable() const;
			void disable() const;
		};
	}
}