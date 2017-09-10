#pragma once

#include <GL/glew.h>
#include <vector>
#include "../maths/maths.h"


namespace bengine
{
	namespace graphics
	{
		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<maths::Matrix4> _transformationStack;
			const maths::Matrix4* _transformationBack;

		protected:

			Renderer2D()
			{
				_transformationStack.push_back(maths::Matrix4::identity());
				_transformationBack = &_transformationStack.back();
			}

		public:
			void push(const maths::Matrix4& matrix, bool override = false)
			{
				if (override)
				{
					_transformationStack.push_back(matrix);
				}
				else
				{
					_transformationStack.push_back(_transformationStack.back() * matrix);
				}

				_transformationBack = &_transformationStack.back();
			}

			void pop()
			{
				if (_transformationStack.size() > 1)
				{
					_transformationStack.pop_back();
				}

				_transformationBack = &_transformationStack.back();
			}

			virtual void begin() {}
			virtual void end() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;
		};
	}
}
