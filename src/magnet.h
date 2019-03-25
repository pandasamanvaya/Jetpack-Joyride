#ifndef MAGNET_H
#define MAGNET_H

#include "main.h"
#include "background.h"
#include "shapes.h"
#include "object.h"

class Magnet{
public :

	Magnet();
	Magnet(float x, float y, float z);
	Object magnet;

	void create_magnet();
	void render_magnet(Background, GLuint);
	void move_left(float);

};

#endif