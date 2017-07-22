#include "batchrenderer2d.h"

namespace bengine
{
	namespace graphics
	{
		BatchRenderer2D::BatchRenderer2D()
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete _ibo;
			delete _indices;
			glDeleteBuffers(1, &_vbo);
		}

		void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &_vao);
			glGenBuffers(1, &_vbo);

			glBindVertexArray(_vao);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo); // vbo is now the array buffer
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOUR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)nullptr);
			glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::colour)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			_indices = new GLuint[RENDERER_INDICES_SIZE]; // we need to allocate this on heap, otherwise we'll get stack overflow.

			// 4 vertices, 6 indices
			for (int i = 0, offset = 0; i < RENDERER_INDICES_SIZE; i += 6, offset += 4)
			{
				_indices[i]	   = offset + 0;
				_indices[i + 1] = offset + 1;
				_indices[i + 2] = offset + 2;

				_indices[i + 3] = offset + 2;
				_indices[i + 4] = offset + 3;
				_indices[i + 5] = offset + 0;
			}

			_ibo = new IndexBuffer(_indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{
			const maths::Vector3& position = renderable->getPosition();
			const maths::Vector2& size = renderable->getSize();
			const maths::Vector4& colour = renderable->getColour();

			int r = colour.x * 255;
			int g = colour.y * 255;
			int b = colour.z * 255;
			int a = colour.w * 255;

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			_buffer->vertex = position;
			_buffer->colour = c;
			_buffer++;

			_buffer->vertex = maths::Vector3(position.x, position.y + size.y, position.z);
			_buffer->colour = c;
			_buffer++;

			_buffer->vertex = maths::Vector3(position.x + size.x, position.y + size.y, position.z);
			_buffer->colour = c;
			_buffer++;

			_buffer->vertex = maths::Vector3(position.x + size.x, position.y, position.z);
			_buffer->colour = c;
			_buffer++;

			_indexCount += 6;
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush()
		{
			glBindVertexArray(_vao);
			_ibo->bind();

			glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, nullptr);

			_ibo->unbind();
			glBindVertexArray(0);

			_indexCount = 0;
		}
	}
}
