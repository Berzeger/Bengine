#pragma once

#include <FreeImage.h>
#include <string>
#include <GL/glew.h>
#include "../utils/imageloader.h"

namespace bengine
{
	namespace graphics
	{
		class Texture
		{
		private:
			std::string _filename;
			GLuint _tid;
			GLsizei _width, _height;

			GLuint load();
		public:
			Texture(const std::string& path);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const GLsizei getWidth() const { return _width; }
			inline const GLsizei getHeight() const { return _height; }
		};
	}
}