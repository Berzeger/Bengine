#include "static_sprite.h"

namespace bengine
{
	namespace graphics
	{
		StaticSprite::StaticSprite(float x, float y, float width, float height, const maths::Vector4& colour, Shader& shader)
			: Renderable2D(maths::Vector3(x, y, 0), maths::Vector2(width, height), colour), _shader(shader)
		{
			_vertexArray = new VertexArray();

			GLfloat vertices[] = {
				0, 0, 0,
				0, height, 0,
				width, height, 0,
				width, 0, 0
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

		StaticSprite::~StaticSprite()
		{
			delete _vertexArray;
			delete _indexBuffer;
		}
	}
}