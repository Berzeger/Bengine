#include <iostream>

#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src/graphics/shader.h"

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

	Window window("Bengine!", 800, 600);
	glClearColor(.2f, .3f, .8f, 1.0f);
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");

	while (!window.closed())
	{
		window.clear();

		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);

		window.update();
	}

	system("PAUSE");
	return 0;
}