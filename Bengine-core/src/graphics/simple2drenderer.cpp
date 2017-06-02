#include "simple2drenderer.h"

namespace bengine
{
	namespace graphics
	{
		void Simple2DRenderer::submit(const Renderable2D* renderable)
		{
			_renderQueue.push_back(renderable);
		}

		void Simple2DRenderer::flush()
		{
			while (!_renderQueue.empty())
			{
				const Renderable2D* renderable = _renderQueue.front();
				renderable->getVAO()->bind();
				renderable->getIBO()->bind();

				renderable->getShader().setUniformMat4("ml_matrix", maths::Matrix4::translation(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				renderable->getIBO()->unbind();
				renderable->getVAO()->unbind();

				_renderQueue.pop_front();
			}
		}
	}	
}
