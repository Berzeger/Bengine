#include "indexbuffer.h"

namespace bengine
{
	namespace graphics
	{
		IndexBuffer::IndexBuffer(GLuint * data, GLsizei count)
			: _count(count)
		{
			glGenBuffers(1, &_bufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &_bufferId);
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
		}

		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
