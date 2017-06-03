#pragma once

#include "renderer2d.h"
#include "buffers/vertexarray.h"

namespace bengine
{
	namespace graphics
	{
		class BatchRenderer2D : public Renderer2D
		{
		private:
			VertexArray _vao;
			GLuint _vbo, _ibo;

		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};
	}
}