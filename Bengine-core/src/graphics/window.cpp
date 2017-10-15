#include "window.h"

namespace bengine
{
	namespace graphics
	{
		void window_resize(GLFWwindow * window, int width, int height);

		Window::Window(const char * title, int width, int height)
		{
			_title = title;
			_width = width;
			_height = height;
			if (!init())
			{
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; ++i)
			{
				_keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; ++i)
			{
				_mouseButtons[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::update()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				std::cout << "OpenGL Error: " << gluErrorString(error) << " (" << error << ")" << std::endl;
			}

			glfwPollEvents();
			glfwSwapBuffers(_window);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(_window) == 1;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW." << std::endl;
				return false;
			}

			_window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);

			if (!_window)
			{
				std::cout << "Failed to create GLFW window." << std::endl;
				return false;
			}

			glfwMakeContextCurrent(_window);
			glfwSetWindowUserPointer(_window, this);
			glfwSetWindowSizeCallback(_window, window_resize);
			glfwSetKeyCallback(_window, key_callback);
			glfwSetMouseButtonCallback(_window, mouse_button_callback);
			glfwSetCursorPosCallback(_window, cursor_position_callback);
			glfwSwapInterval(0); // vsync off

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GLEW." << std::endl;
				return false;
			}
			
			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;	

			return true;
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			// TODO: Log this
			if (keycode >= MAX_KEYS)
			{
				return false;
			}

			return _keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			// TODO: Log this
			if (button >= MAX_BUTTONS)
			{
				return false;
			}

			return _mouseButtons[button];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = _mx;
			y = _my;
		}

		void window_resize(GLFWwindow * window, int width, int height)
		{
			glViewport(0, 0, width, height);

			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->setHeight(height);
			win->setWidth(width);
		}

		void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->_keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->_mouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->_mx = xpos;
			win->_my = ypos;
		}
	}
}
