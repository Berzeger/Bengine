#include "batchrenderer2d.h"

namespace bengine
{
	namespace graphics
	{
		BatchRenderer2D::BatchRenderer2D()
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete _ibo;
			glDeleteBuffers(1, &_vbo);
		}

		void BatchRenderer2D::init()
		{
			glGenBuffers(1, &_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{

		}

		void BatchRenderer2D::flush()
		{

		}
	}
}