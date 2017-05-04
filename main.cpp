#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "InputHandler.h"
#include <Windows.h>
#include <glm\glm.hpp>
#include "World.h"
#include "Triangle.h"
#include "Plane.h"
#include "Cube.h"
#include <memory>

std::unique_ptr<InputHandler> input;
void key_input_cb(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursor_position_cb(GLFWwindow* window, double _xpos, double _ypos);

//int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
int main(){
	if (!glfwInit()) {
		std::cout << "fail" << std::endl;
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow * window = glfwCreateWindow(900, 500, "Playground", NULL, NULL);
	if (!window) {
		std::cout << "fail" << std::endl;
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cout << "glew not initialized." << std::endl;
		return 1;
	}
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	std::shared_ptr<World> world = std::make_shared<World>();
	InputHandler inputHandler(world, window);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, &key_input_cb);
	glfwSetCursorPosCallback(window, &cursor_position_cb);

	world->addItem(std::make_shared<Cube>("simpleTriangleVertex.glsl", "simpleTriangleFragment.glsl",world));
	world->addItem(std::make_shared<Triangle>("simpleTriangleVertex.glsl", "simpleTriangleFragment.glsl",world));
	auto ground = std::shared_ptr<Plane>("simpleTriangleVertex.glsl", "simpleTriangleFragment.glsl",world);
	//ground->rotate(3.1415/2, glm::vec3(1,0,0));
	//ground->move(glm::vec3(0,1,0));
	//ground->scale(glm::vec3(4,4,0));
	//ground->setTo(glm::vec3(-1.5f,0.5f,-5.f),glm::vec3(1.5f, 0.5f, 5.f));
	world->addItem(ground);
	input = std::make_unique<InputHandler>(world, window);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3, 0.1, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world->draw();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void key_input_cb(GLFWwindow *window, int key, int scancode, int action, int mods) {
	input->key_input(window, key, scancode, action, mods);
}

void cursor_position_cb(GLFWwindow* window, double _xpos, double _ypos) {
	input->cursor_input(window, _xpos, _ypos);
}