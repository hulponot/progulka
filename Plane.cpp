#include "Plane.h"
#include "World.h"
#include <glm\gtc\matrix_transform.hpp>


Plane::Plane(std::string v, std::string f, std::weak_ptr<World>w) : Object(v, f, w)
{
	GLfloat points[] = {
		-50.5f,  -50.5f,  0.0f,		0.0f,  50.f, //left bot
		-50.5f, 50.5f,  0.0f,		0.f,  0.f, //left top
		50.5f, 50.5f,  0.0f,		50.f,  0.f, //right top
		50.5f, -50.5f,  0.0f,		50.f,  50.f //right bot
	};
	GLuint indicies_tmp[] = {
		0, 3, 1,
		1, 3, 2
	};
	
	textureID = ShaderLoader::CreateTexture("res/terrain_BMP_DXT5_1.DDS");

	coords = new GLfloat[sizeof(points)];
	memcpy(coords, points, sizeof(points));
	indicies = new GLuint[sizeof(indicies_tmp)];
	memcpy(indicies, indicies_tmp, sizeof(indicies_tmp));
	glGenBuffers(1, &coordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(GLfloat), coords, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indicies, GL_STATIC_DRAW);
	
	T = glm::mat4(1.0f);
	R = glm::mat4(1.0f);
	S = glm::mat4(1.0f);
	glUseProgram(program);
	mainLightlocation = glGetUniformLocation(program, "mainLight");
	matTlocation = glGetUniformLocation(program, "matT");
	matRlocation = glGetUniformLocation(program, "matR"); 
	matSlocation = glGetUniformLocation(program, "matS");
	matViewlocation = glGetUniformLocation(program, "matView");
	matProjlocation = glGetUniformLocation(program, "matProj");
	textureLocation = glGetUniformLocation(program, "textureSampler");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


Plane::~Plane()
{
	delete[] coords;
	delete[] indicies;
	glDeleteBuffers(1, &coordBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vao);
}


void Plane::draw() {
	glUseProgram(program);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glEnableVertexAttribArray(1);
	if (auto w = world.lock()) {
		auto projMat = w->getProjMat();
		auto viewMat = w->getViewMat();
		glUniformMatrix4fv(matViewlocation, 1, GL_FALSE, glm::value_ptr(*viewMat.get()));
		glUniformMatrix4fv(matProjlocation, 1, GL_FALSE, glm::value_ptr(*projMat.get()));
	}
	glUniformMatrix4fv(matTlocation, 1, GL_FALSE, &T[0][0]);
	glUniformMatrix4fv(matSlocation, 1, GL_FALSE, &S[0][0]);
	glUniformMatrix4fv(matRlocation, 1, GL_FALSE, &R[0][0]);
	glUniform3fv(mainLightlocation, 1, &World::getMainLight()[0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(textureLocation, 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void Plane::setTo(glm::vec3 uL, glm::vec3 bR) {
	coords[0] = uL.x;
	coords[1] = bR.y;
	coords[2] = bR.z;

	coords[3+3*1] = uL.x;
	coords[4+3*1] = uL.y;
	coords[5+3*1] = bR.z;

	coords[6+3*2] = bR.x;
	coords[7+3*2] = uL.y;
	coords[8+3*2] = bR.z;

	coords[9+3*3] = bR.x;
	coords[10 + 3 * 3] = bR.y;
	coords[11 + 3 * 3] = bR.z;
	
	glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), coords, GL_STATIC_DRAW);
}
