#pragma once

#include "../renderable2d.h"

namespace bengine
{
	namespace graphics
	{
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> _renderables;
			maths::Matrix4 _transformationMatrix;

		public:
			Group(const maths::Matrix4& transform);
			void add(Renderable2D * renderable);
			void submit(Renderer2D * renderer) const override;
		};
	}
}
