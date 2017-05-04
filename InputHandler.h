
#include <GLFW\glfw3.h>
#pragma once

#include "World.h"
#include "Plane.h"
#include <memory>
class InputHandler
{
protected:
	std::weak_ptr<World> world;

	double xpos, ypos;
	double hAngle, vAngle;
public:
	void key_input(GLFWwindow *window, int key, int scancode, int action, int mods) {
		if (auto _world = world.lock()) {
			if (key == GLFW_KEY_ESCAPE) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			if (key == GLFW_KEY_1) {
				/*Plane* plane = (Plane*)world->getPlayer();
				if (plane != NULL) {
					plane->setTo(glm::vec3(-1, 1, 0), glm::vec3(1, -1, 0));
				}*/
			}
			if (key == GLFW_KEY_LEFT) {
				/*Object* p = world->getPlayer();
				if (p != NULL) {
					p->rotate(0.3f, glm::vec3(0.0f, 1.0f, 0.0f));
				}*/
			}
			if (key == GLFW_KEY_UP) {
				/*Object* p = world->getPlayer();
				if (p != NULL) {
					p->rotate(0.3f, glm::vec3(1.0f, 0.0f, 0.0f));
				}*/
			}
			if (key == GLFW_KEY_DOWN) {
				/*Object* p = world->getPlayer();
				if (p != NULL) {
					p->rotate(0.3f, glm::vec3(-1.0f, 0.0f, 0.0f));
				}*/
			}
			if (key == GLFW_KEY_RIGHT) {
				/*Object* p = world->getPlayer();
				if (p != NULL) {
					p->rotate(0.3f, glm::vec3(0.0f, -1.0f, 0.0f));
				}*/
			}
			if (key == GLFW_KEY_KP_SUBTRACT) {
				/*Object* p = world->getPlayer();
				if (p != NULL) {
					p->scale(glm::vec3(0.5f, 0.5f, .5f));
				}*/
			}
			if (key == GLFW_KEY_KP_ADD) {
				/*	Object* p = world->getPlayer();
					if (p != NULL) {
						p->scale(glm::vec3(2.0f, 2.0f, 2.0f));
					}*/
			}
			if (key == GLFW_KEY_W) {
				_world->moveWorld(glm::vec3(0.f, 0.f, -1.f));
			}
			if (key == GLFW_KEY_S) {
				_world->moveWorld(glm::vec3(0.f, 0.f, +1.f));
			}
			if (key == GLFW_KEY_A) {
				_world->moveWorld(glm::vec3(1.f, 0.f, 0.f));
			}
			if (key == GLFW_KEY_D) {
				_world->moveWorld(glm::vec3(-1.f, 0.f, 0.f));
			}
		}
	}

	void cursor_input(GLFWwindow* window, double _xpos, double _ypos)
	{
		if (auto _world = world.lock()) {
			_world->rotateWorld(_xpos, _ypos);
			xpos = _xpos;
			ypos = _ypos;
		}
	}
	InputHandler(std::weak_ptr<World>w,GLFWwindow *);
	~InputHandler();
};

