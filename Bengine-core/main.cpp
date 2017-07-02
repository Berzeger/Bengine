#include <iostream>
#include <time.h>

#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src/utils/timer.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/sprite.h"
#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#define BATCH_RENDERER 1

#ifdef _WIN32
#include <windows.h>

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

int main(char** argv, int argc) 
{
	using namespace bengine;
	using namespace graphics;
	using namespace maths;

	Window window("Bengine!", 960, 540);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Matrix4 ortho = Matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	std::vector<Renderable2D*> sprites;
	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.1f)
	{
		for (float x = 0; x < 16.0f; x += 0.1f)
		{
			sprites.push_back(new 
#if BATCH_RENDERER
				Sprite
#else
				StaticSprite
#endif
				(x, y, 0.08f, 0.08f, maths::Vector4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !BATCH_RENDERER
				, shader
#endif
			));
		}
	}

#if BATCH_RENDERER
	Sprite sprite(5, 5, 4, 4, Vector4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, Vector4(0.2f, 0, 1, 1));
	BatchRenderer2D renderer;
#else
	StaticSprite sprite(5, 5, 4, 4, Vector4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, Vector4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;
#endif

	shader.setUniform2f("light_pos", Vector2(4.0f, 1.5f));
	shader.setUniform4f("colour", Vector4(0.2f, 0.3f, 0.8f, 1.0f));

	Timer timer;
	float time = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Vector2((float)(x * 16.0f / window.getWidth()), (float)(9.0f - y * 9.0f / window.getHeight())));
#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); ++i)
		{
			renderer.submit(sprites[i]);
		}
#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();

		window.update();

		frames++;
		if (timer.elapsed() - time > 1.0f)
		{
			time += 1.0f;
			printf("Rendering %d sprites, %d FPS\n", sprites.size(), frames);
			frames = 0;	
		}
	}

	return 0;
}
