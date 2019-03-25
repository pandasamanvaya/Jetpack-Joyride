#ifndef BOOMERANG_H
#define BOOMERANG_H

#include "main.h"
#include "object.h"
#include "shapes.h"
#include "background.h"

class Boomerang{
public:
	Boomerang();
	Boomerang(float x, float y, float z);

	Object boom;
	bool out = false;
	float turn = 0.4;
	void create_boom();
	void render_boom(Background, GLuint, int);
	void move_boom();
	void set_position(float, float, float);
};

#endif