#include "WindowsWindow.h"
#include <Echo/events/ApplicationEvent.h>
#include <Echo/events/KeyboardEvent.h>
#include <Echo/events/MouseEvent.h>

Echo::Window* Echo::Window::Create(const Echo::WindowSetting& ws)
{
	return new Echo::WindowsWindow(ws);
}

Echo::WindowsWindow::WindowsWindow(const Echo::WindowSetting& ws)
{
	wd.width = ws.width;
	wd.height = ws.height;
	wd.title = ws.title;

	// glfw hints
	//glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);

	// initialize a new window
	glfwInit();

	window = glfwCreateWindow(wd.width, wd.height, wd.title.data(), NULL, NULL);
	if (!window)
		glfwTerminate();

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, &wd);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		LOG_error("glad init failed");

	glViewport(0, 0, ws.width, ws.height);

	// blending
	//glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	// initialize callback functions
	InitCallback();
}

void Echo::WindowsWindow::InitCallback()
{
	// window functions
	glfwSetWindowCloseCallback(window, [](GLFWwindow* w)
		{
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(w);
			WindowCloseEvent event;
			wd.func(event);
		}
	);

	// keyboard functions
	glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(w);
			switch (action)
			{
			case(GLFW_PRESS):
			{
				KeyDownEvent event((char)key, 0);
				wd.func(event);
				break;
			}
			case(GLFW_REPEAT):
			{
				KeyDownEvent event((char)key, 1);
				wd.func(event);
				break;
			}
			case(GLFW_RELEASE):
			{
				KeyUpEvent event((char)key);
				wd.func(event);
				break;
			}
			}
		}
	);

	// mouse functions
	glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods)
		{
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(w);
			switch (action)
			{
			case(GLFW_PRESS):
			{
				MouseDownEvent event(button);
				wd.func(event);
				break;
			}
			case(GLFW_RELEASE):
			{
				MouseUpEvent event(button);
				wd.func(event);
				break;
			}
			}
		}
	);

	glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y)
		{
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(w);
			MouseMoveEvent event((float)x, (float)y);
			wd.func(event);
		}
	);

	glfwSetScrollCallback(window, [](GLFWwindow* w, double x, double y)
		{
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(w);
			MouseWheelEvent event((float)x, (float)y);
			wd.func(event);
		}
	);
}

void Echo::WindowsWindow::Update()
{
	// swap buffers and poll for events
	glfwSwapBuffers(window);
	glfwPollEvents();
}

Echo::WindowsWindow::~WindowsWindow()
{
	LOG_erase("terminate program");
	glfwTerminate();
}