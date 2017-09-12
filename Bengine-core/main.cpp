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

#include <FreeImage.h>

#define BATCH_RENDERER 1
#define TEST_50K_SPRITES 0

#ifdef _WIN32
#include <windows.h>

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

#if 0
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

#endif

int main()
{
	const char * filename = "test.png";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return 1;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return 1;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return 1;

	std::cout << width << ", " << height;

	FreeImage_Unload(dib);

	return 0;
}