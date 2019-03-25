#ifndef COIN_H
#define COIN_H

#include "main.h"
#include "background.h"
#include "shapes.h"
#include "object.h"

class Coin{
public:
	Coin(){};
	Coin(const float color[], float x, float y, float z);

	Object coin;

	void set_position(GLfloat *, float *);
	void create_coin();
	void render_coin(Background, GLuint);
	void move_left(float);
};

#endif