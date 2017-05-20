#pragma once

#include <GL/glew.h>

namespace bengine
{
	namespace graphics
	{
		class IndexBuffer
		{
		private:
			GLuint _bufferId;
			GLuint _count;

		public:
			IndexBuffer(GLushort * data, GLsizei count);

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return _count; }
		};
	}
}