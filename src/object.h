#ifndef _OBJECT_H
#define _OBJECT_H

#include <GLFW/glfw3.h>

#define MAX 10000

class Object{
public:

	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLfloat boundary[MAX];
	GLfloat color_data[MAX];	
	int len = 0;
	vec3 position = vec3(0.0, 0.0, 0.0);

};

#endif