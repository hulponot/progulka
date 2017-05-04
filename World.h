#pragma once

#include <GLFW\glfw3.h>
#include <vector>

#include "Object.h"

using std::vector;
class World
{
private:
	double time;
	vector<std::weak_ptr<Object>> items;

	static glm::vec3 mainLight;

	static glm::vec3 eye;
	static glm::vec3 center;
	static glm::vec3 up;

	std::shared_ptr<glm::mat4> Proj;
	std::shared_ptr<glm::mat4> View;
public:
	static glm::vec3& getMainLight();

	void  addItem(std::weak_ptr<Object>);
	void draw();
	std::shared_ptr<glm::mat4> getProjMat();
	std::shared_ptr<glm::mat4> getViewMat();
	World();
	~World();

	void rotateWorld(double, double);
	void moveWorld(glm::vec3);
};

