#include "Triangle.h"
#include <glm\gtc\matrix_transform.hpp>


Triangle::~Triangle()
{
}

void Triangle::move() {

}
Triangle::Triangle(std::string v, std::string f, std::weak_ptr<World> w) : Object(v, f, w) {
	GLfloat points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};
	coords = points;

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), coords, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	T = glm::mat4(1.0f);

	T = glm::scale(T, glm::vec3(2,2,1));
	glUseProgram(program);
	matTlocation = glGetUniformLocation(program, "matT");
}

void Triangle::draw(){
	glUseProgram(program);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glUniformMatrix4fv(matTlocation, 1, GL_FALSE, &T[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}