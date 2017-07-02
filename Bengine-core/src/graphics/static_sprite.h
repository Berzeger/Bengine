#pragma once

#include "renderable2d.h"

namespace bengine
{
	namespace graphics
	{
		class StaticSprite : public Renderable2D
		{
		private:
			VertexArray* _vertexArray;
			IndexBuffer* _indexBuffer;
			Shader& _shader;

		public:
			StaticSprite(float x, float y, float width, float height, const maths::Vector4& colour, Shader& shader);
			~StaticSprite();

			inline const VertexArray* getVAO() const { return _vertexArray; }
			inline const IndexBuffer* getIBO() const { return _indexBuffer; }

			inline Shader& getShader() const { return _shader; }
		};
	}
}
