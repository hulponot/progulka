#include "Object.h"

#include <glm\gtc\matrix_transform.hpp>

Object::Object(std::string vertexShaderFile, std::string fragmentShaderFile, std::weak_ptr<World> w)
{
	program = ShaderLoader::loadShader(vertexShaderFile.c_str(), fragmentShaderFile.c_str());
	world = w;
}


Object::~Object()
{
	glDeleteProgram(program);
}


void Object::move(glm::vec3 v) {
	T = glm::translate(T, v);
}
void Object::rotate(float angle, glm::vec3 v) {
	R = glm::rotate(R, angle, v);
}
void Object::scale(glm::vec3 v) {
	S = glm::scale(S, v);
}