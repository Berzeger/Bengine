#include <iostream>

#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

int main(char** argv, int argc) 
{
	using namespace bengine;
	using namespace graphics;
	using namespace maths;

	Window window("Bengine!", 800, 600);
	glClearColor(.2f, .3f, .8f, 1.0f);
	Vector2 vec(1.0f, 2.0f);					//vec = (1, 2)
	std::cout << vec << std::endl;
	Vector3 vec2(1.0f, 2.0f, 3.0f);				//vec2 = (1, 2, 3)
	Vector3 vec3 = vec2 + Vector3(4, 4, 4);		//vec3 = (5, 6, 7)

	Vector4 vec4(1, 1, 5, 6);					//vec4 = (1, 1, 5, 6)
	Vector4 vec5 = vec4 - Vector4(1, 2, 3, 8);	//vec5 = (0, -1, 2, -2)

	Matrix4 position = Matrix4::translation(Vector3(2, 3, 4));
	position *= Matrix4::identity();

	std::cout << vec2 << std::endl;
	std::cout << vec3 << std::endl;
	std::cout << vec4 << std::endl;
	std::cout << vec5 << std::endl;

	//std::string file = read_file("main.cpp");
	//std::cout << file << std::endl;
	
	while (!window.closed())
	{
		//std::cout << window.getWidth() << ", " << window.getHeight() << std::endl;
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_A))
			std::cout << "PRESSED!" << std::endl;

		double x, y;
		window.getMousePosition(x, y);
		//std::cout << x << ", " << y << std::endl;

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f,  0.5f);
		glVertex2f( 0.5f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
		window.update();
	}

	system("PAUSE");
	return 0;
}