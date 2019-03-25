#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "main.h"

#define GLFW_FAIL 1
#define GLEW_FAIL 2

class Background{

public:

	mat4 project = mat4(1.0f);

	GLFWwindow* create_window(int, int);
	void render_object();
	void render_texture(GLuint);
	void disable();
	GLuint render_player();
	void render_all();
	mat4 position_object(vec3);
	void reshapeWindow(GLFWwindow *, int, int, float);
};

#endif