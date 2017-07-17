#pragma once

#include "layer.h"
#include "../batchrenderer2d.h"

namespace bengine
{
	namespace graphics
	{
		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			virtual ~TileLayer();
		};
	}
}	
