#include "World.h"
#include <glm\gtc\matrix_transform.hpp>

glm::vec3 World::mainLight = glm::vec3(5.0f,10.0f,0.0f);

glm::vec3& World::getMainLight() {
	return mainLight;
}
World::World()
{
	time = glfwGetTime();

	Proj = std::make_shared<glm::mat4>(glm::perspective(30.0f, (float)900 / (float)500, 0.01f, 10.0f));
	eye = glm::vec3(0.f, 0.f, 1.f);
	center = glm::vec3(0.f, 0.f, -1.f);
	up = glm::vec3(0.f, 1.0f, 0.f);
	View = std::make_shared<glm::mat4>(glm::lookAt(eye, center, up));
}


World::~World()
{

}

void World::draw() {
	for each (auto item in items)
	{
		if (auto i = item.lock()) {
			i->draw();
		}
	}
}

void World::addItem(std::weak_ptr<Object>i) {
	items.push_back(i);
}

void World::rotateWorld(double dx, double dy) {
	dx *= 0.01;
	dy *= 0.01;
	center.x = -cos(dx);
	center.y = sin(dy);
	center.z = sin(dx);
	//center.z += -cos(dy);
	View = std::make_shared<glm::mat4>(glm::lookAt(eye, eye + center, up));
}


void World::moveWorld(glm::vec3 v) {
	eye += v*0.1f;
	View = std::make_shared<glm::mat4>(glm::lookAt(eye, eye + center, up));
};

std::shared_ptr<glm::mat4> World::getProjMat() {
	return Proj;
}
std::shared_ptr<glm::mat4> World::getViewMat() {
	return View;
}