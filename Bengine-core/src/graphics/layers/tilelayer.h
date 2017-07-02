#pragma once

#include "layer.h"

namespace bengine
{
	namespace graphics
	{
		class TileLayer
		{
		public:
			TileLayer(Renderer2D* renderer, Shader* shader, maths::Matrix4 projectionMatrix);
			virtual ~TileLayer();
			virtual void add(Renderable2D* renderable);
			virtual void render();
		};
	}
}	
