#pragma once
#include "Object.h"
#include <string>

class Triangle :
	public Object
{
public:
	void draw();
	void move();
	Triangle(std::string v, std::string f, std::weak_ptr<World> w);
	~Triangle();
};

