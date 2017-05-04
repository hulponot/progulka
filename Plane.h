#pragma once
#include "Object.h"

class Plane :
	public Object
{
public:
	Plane(std::string, std::string, std::weak_ptr<World> w);
	void setTo(glm::vec3 upperLeft, glm::vec3 bottomRight);
	~Plane();
	void draw();
};

