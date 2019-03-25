#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"
#include "background.h"
#include "shapes.h"
#include "object.h"
#include "timer.h"

class Player{

public:

	Player();
	Player(float x, float y, float z);
	Object man;

	void create_player();
	void render_player(Background, GLuint);
	void jump(float);
	void fall(float);
	void change_color(const float[]);
};

#endif