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
		struct VertexData
		{
			maths::Vector3 vertex;
			unsigned int colour;
		};

		class Renderable2D
		{
		public:
			maths::Vector3 _position;
			maths::Vector2 _size;
			maths::Vector4 _colour;

			Renderable2D(maths::Vector3 position, maths::Vector2 size, maths::Vector4 colour)
				: _position(position), _size(size), _colour(colour)
			{ }

			virtual ~Renderable2D()	{ }

			inline const maths::Vector3& getPosition() const { return _position; }
			inline const maths::Vector2& getSize() const { return _size; }
			inline const maths::Vector4& getColour() const { return _colour; }
		};
	}
}
