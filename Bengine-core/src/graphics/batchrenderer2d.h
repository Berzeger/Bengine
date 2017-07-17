#pragma once

#include "renderer2d.h"
#include "buffers/indexbuffer.h"

namespace bengine
{
	namespace graphics
	{
#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4					// 4 vertices for 1 sprite
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES // memory to hold all sprites
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6					// 6 indices per sprite

#define SHADER_VERTEX_INDEX		0
#define SHADER_COLOUR_INDEX		1

		class BatchRenderer2D : public Renderer2D
		{
		private:
			GLuint _vao;
			GLuint _vbo;
			VertexData* _buffer;
			GLuint* _indices;

			IndexBuffer* _ibo;
			GLsizei _indexCount;

			void init();

		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void end() override;
			void flush() override;
		};
	}
}
