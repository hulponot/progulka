#ifndef OBJECT_H_
#define OBJECT_H_
#include <string>
#include "ShaderLoader.h"
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <memory>
class World;

class Object
{
protected:
	std::weak_ptr<World> world;

	std::string vertexShaderFile;
	std::string fragmentShaderFile;
	GLuint program;
	GLfloat *coords;
	GLuint *indicies;
	GLuint vao;
	GLuint coordBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;
	GLuint textureID;
	GLuint textureLocation;

	GLuint matTlocation;
	GLuint matSlocation;
	GLuint matRlocation;
	GLuint matProjlocation;
	GLuint matViewlocation;

	GLuint mainLightlocation;

	glm::mat4 T;
	glm::mat4 R;
	glm::mat4 S;
public:
	virtual void draw() = 0;
	void move(glm::vec3);
	void rotate(float angle, glm::vec3);
	void scale(glm::vec3);

	Object(std::string, std::string, std::weak_ptr<World> w);
	~Object();
};

#endif // !OBJECT_H_