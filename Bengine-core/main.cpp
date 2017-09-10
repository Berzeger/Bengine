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
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"

#define BATCH_RENDERER 1
#define TEST_50K_SPRITES 0

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

	Shader *shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader *shader2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");

	shader->enable(); 
	shader->setUniform2f("light_pos", Vector2(4.0f, 1.5f));
	shader2->enable();
	shader2->setUniform2f("light_pos", Vector2(4.0f, 1.5f));

	TileLayer layer(shader);
	
#if TEST_50K_SPRITES
	for (float y = -9.0f; y < 9.0f; y += 0.1f)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1f)
		{
			layer.add(new Sprite(x, y, 0.09f, 0.09f, Vector4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
#else
	//for (float y = -9.0f; y < 9.0f; y++)
	//{
	//	for (float x = -16.0f; x < 16.0f; x++)
	//	{
	//		layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::Vector4(rand() % 1000 / 1000.0f, 0, 1, 1)));
	//	}
	//}

	Matrix4 transform = Matrix4::translation(Vector3(-15.0f, 5.0f, 0.0f)) * Matrix4::rotation(45, Vector3(0, 0, 1));
	Group * group = new Group(transform);
	group->add(new Sprite(0, 0, 6, 3, Vector4(1, 1, 1, 1)));

	Group * button = new Group(Matrix4::translation(Vector3(0.5f, 0.5f, 0.0f)));
	button->add(new Sprite(0, 0, 5.0f, 2.0f, Vector4(1, 0, 1, 1)));
	button->add(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, Vector4(0.2f, 0.3f, 0.8f, 1)));
	group->add(button);

	layer.add(group);
#endif

	//TileLayer layer2(shader2);
	//layer2.add(new Sprite(-2, -2, 4, 4, Vector4(1, 0, 1, 1)));
	
	Timer timer;
	float time = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);

		shader->enable(); 
		shader->setUniform2f("light_pos", Vector2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));

		layer.render();

		window.update();

		frames++;
		if (timer.elapsed() - time > 1.0f)
		{
			time += 1.0f;
			printf("%d FPS\n", frames);
			frames = 0;	
		}
	}

	return 0;
}
