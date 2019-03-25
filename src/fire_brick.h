#ifndef FIRE_BRICK_H
#define FIRE_BRICK_H

#include "main.h"
#include "object.h"
#include "shapes.h"
#include "background.h"
#include "timer.h"

class FireLine{
public:
	FireLine();
	FireLine(float x, float y, float z);

	Object fire;
	void create_block();
	void oscillate();
	void render_block(Background, GLuint);
	void move_left(float);
	void set_position(float, float, float);

};

class FireBeam{
public:
	FireBeam();
	FireBeam(float x, float y, float z);

	Object fire;
	int dir = 0;
	void create_block();
	void render_block(Background, GLuint);
	void move_up_down(int i);
	void set_position(float, float, float, int);

};

#endif