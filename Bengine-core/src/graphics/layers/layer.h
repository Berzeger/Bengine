#pragma once

#include "../renderer2d.h"
#include "../renderable2d.h"

namespace bengine
{
	namespace graphics
	{
		class Layer
		{
		protected:
			Renderer2D* _renderer;
			std::vector<Renderable2D*> _renderables;
			Shader* _shader;
			maths::Matrix4 _projectionMatrix;

			Layer(Renderer2D* renderer, Shader* shader, maths::Matrix4 projectionMatrix);
		
		public:
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();
		};
	}
}
