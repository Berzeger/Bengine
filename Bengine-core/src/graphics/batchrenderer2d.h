#pragma once

#include "renderer2d.h"
#include "buffers/vertexarray.h"

namespace bengine
{
	namespace graphics
	{
#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4					// 4 vertices for 1 sprite
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES // memory to hold all sprites
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6					// 6 indices per sprite

		class BatchRenderer2D : public Renderer2D
		{
		private:
			VertexArray _vao;
			IndexBuffer* _ibo;
			GLsizei _indexCount;
			GLuint _vbo;

			void init();

		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};
	}
}