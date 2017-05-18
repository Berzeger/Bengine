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

	Window window("Bengine!", 960, 540);
	glClearColor(.2f, .3f, .8f, 1.0f);
	
	GLfloat vertices[] = 
	{
		4, 3, 0,
		12, 3, 0,
		4, 6, 0,
		4, 6, 0,
		12, 6, 0,
		12, 3, 0

		//-0.5f, -0.5f, 0.0f,
		//-0.5f,  0.5f, 0.0f,
		// 0.5f,  0.5f, 0.0f,
		// 0.5f,  0.5f, 0.0f,
		// 0.5f, -0.5f, 0.0f,
		//-0.5f, -0.5f, 0.0f
	};

	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	Matrix4 ortho = Matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	//glUniformMatrix4fv(glGetUniformLocation(shader._shaderId, "pr_matrix"), 1, GL_FALSE, ortho.elements);

	while (!window.closed())
	{
		window.clear();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.update();
	}

	return 0;
}