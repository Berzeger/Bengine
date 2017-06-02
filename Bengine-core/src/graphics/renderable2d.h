#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "../maths/maths.h"
#include "shader.h"

namespace bengine
{
	namespace graphics
	{
		class Renderable2D
		{
		public:
			maths::Vector3 _position;
			maths::Vector2 _size;
			maths::Vector4 _colour;

			VertexArray* _vertexArray;
			IndexBuffer* _indexBuffer;
			Shader& _shader;

			Renderable2D(maths::Vector3 position, maths::Vector2 size, maths::Vector4 colour, Shader& shader)
				: _position(position), _size(size), _colour(colour), _shader(shader)
			{
				_vertexArray = new VertexArray();

				GLfloat vertices[] = {
					0, 0, 0,
					0, size.y, 0,
					size.x, size.y, 0,
					size.x, 0, 0
				};

				GLfloat colours[] = {
					colour.x, colour.y, colour.z, colour.w,
					colour.x, colour.y, colour.z, colour.w,
					colour.x, colour.y, colour.z, colour.w,
					colour.x, colour.y, colour.z, colour.w
				};

				_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				_vertexArray->addBuffer(new Buffer(colours, 4 * 4, 4), 1);

				GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
				_indexBuffer = new IndexBuffer(indices, 6);
			}

			virtual ~Renderable2D()
			{
				delete _vertexArray;
				delete _indexBuffer;
			}

			inline const VertexArray* getVAO() const { return _vertexArray; }
			inline const IndexBuffer* getIBO() const { return _indexBuffer; }

			inline Shader& getShader() const { return _shader; }

			inline const maths::Vector3& getPosition() const { return _position; }
			inline const maths::Vector2& getSize() const { return _size; }
			inline const maths::Vector4& getColour() const { return _colour; }
		};
	}
}