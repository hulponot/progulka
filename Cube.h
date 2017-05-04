#pragma once
#include "Object.h"

class Cube : public Object
{
public:
	Cube(std::string v, std::string f, std::weak_ptr<World> w);
	~Cube();
	void draw();
};

