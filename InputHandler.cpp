#include "InputHandler.h"
#include <GLFW\glfw3.h>

InputHandler::InputHandler(std::weak_ptr<World> w, GLFWwindow *window)
{
	world = w;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (auto _world = world.lock()) {
		_world->rotateWorld(xpos, ypos);
	}
	hAngle = 0.0f;
	vAngle = 0.0f;
}


InputHandler::~InputHandler()
{
}
