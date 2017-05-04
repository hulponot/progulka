#include "Cube.h"
#include <glm\gtc\matrix_transform.hpp>
#include "World.h"


Cube::Cube(std::string v, std::string f, std::weak_ptr<World> w) : Object(v, f, w)
{

	GLfloat points[] = {
		-0.5f,  -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f,  -0.5f,  -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  -0.5f, 0.0f, 0.0f, 1.0f
	};
	GLuint indicies_tmp[] = {
		0, 3, 2,
		0, 2, 1,

		4, 5, 7,
		5, 6, 7,

		1, 2, 5,
		5, 2, 6,

		1, 5, 0,
		0, 5, 4,

		2, 7, 6,
		3, 7 ,2,

		0, 4, 7,
		0, 7, 3

	};
	//coords = points;
	//indicies = indicies_tmp;
	
	coords = new GLfloat[sizeof(points)/sizeof(GLfloat)];
	memcpy(coords, points, sizeof(points));
	indicies = new GLuint[sizeof(indicies_tmp) / sizeof(GLuint)];
	memcpy(indicies, indicies_tmp, sizeof(indicies_tmp));
	
	
	glGenBuffers(1, &coordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
	glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(GLfloat), coords, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), NULL);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*2*3 * sizeof(GLuint), indicies, GL_STATIC_DRAW);

	T = glm::mat4(1.0f);
	R = glm::mat4(1.0f);
	S = glm::mat4(1.0f);

	glUseProgram(program);
	mainLightlocation = glGetUniformLocation(program, "mainLight");
	matTlocation = glGetUniformLocation(program, "matT");
	matRlocation = glGetUniformLocation(program, "matR");
	matSlocation = glGetUniformLocation(program, "matS");
	matProjlocation = glGetUniformLocation(program, "matProj");
	matViewlocation = glGetUniformLocation(program, "matView");
}


Cube::~Cube()
{
	delete[] coords;
	delete[] indicies;
	glDeleteBuffers(1, &coordBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vao);
}

void Cube::draw() {
	glUseProgram(program);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	if (auto w = world.lock()) {
		auto projMat = w->getProjMat();
		auto viewMat = w->getViewMat();
		glUniformMatrix4fv(matViewlocation, 1, GL_FALSE, glm::value_ptr<glm::mat4>(viewMat->get()));
		glUniformMatrix4fv(matProjlocation, 1, GL_FALSE, glm::value_ptr<glm::mat4>(projMat));
	}
	glUniformMatrix4fv(matTlocation, 1, GL_FALSE, &T[0][0]);
	glUniformMatrix4fv(matSlocation, 1, GL_FALSE, &S[0][0]);
	glUniformMatrix4fv(matRlocation, 1, GL_FALSE, &R[0][0]);
	glUniform3fv(mainLightlocation, 1, &World::getMainLight()[0]);
	glDrawElements(GL_TRIANGLES, 6*2*3, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}