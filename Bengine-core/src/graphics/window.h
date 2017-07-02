#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace bengine
{
	namespace graphics
	{
#define MAX_KEYS		1024
#define MAX_BUTTONS		32

		class Window
		{
		private:
			friend struct GLFWWindow;

			const char * _title;
			int _width, _height;
			GLFWwindow* _window;

			bool _keys[MAX_KEYS];
			bool _mouseButtons[MAX_BUTTONS];
			double _mx, _my;

			bool init();
			friend static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);

		public:
			Window(const char * name, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;
			inline int getWidth() const { return _width; }
			inline int getHeight() const { return _height; }
			inline void setWidth(int width) { _width = width; }
			inline void setHeight(int height) { _height = height; }

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;
		};
	}
}
