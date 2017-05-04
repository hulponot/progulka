#pragma once

#ifndef __GL_H__
	#include <GL\glew.h>
#endif

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class ShaderLoader
{
public:
	static int loadShader(const char *vertex_path, const char *fragment_path);
	static std::string readFile(const char*);
	static GLuint CreateTexture(char const* imagepath);
	ShaderLoader();
	~ShaderLoader();
};