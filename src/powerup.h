#ifndef POWERUP_H
#define POWERUP_H

#include "main.h"
#include "background.h"
#include "shapes.h"
#include "object.h"
#include "player.h"
#include "timer.h"

class Shield{
public:

	Shield();
	Shield(float x, float y, float z);
	Object cover;

	void create_shield();
	void render_shield(Background, GLuint);
	void move_on_screen();
	void move_left(float);
	void set_position(float, float, float);
};

class Heart{
public:

	Heart();
	Heart(float x, float y, float z);
	Object life;

	void create_heart();
	void render_heart(Background, GLuint);
	void move_on_screen();
	void move_left(float);
	void set_position(float, float, float);

};

class WaterBalloon{
public:

	WaterBalloon();
	WaterBalloon(float x, float y, float z);
	vec3 icon_position = vec3(1.0f);
	GLuint icon_vertexbuffer;
	GLuint icon_colorbuffer;
	GLfloat icon[2000];
	GLfloat icon_color[2000];
	int icon_len = 0;
	Object water;
	bool press = false;
	
	void create_balloon();
	void render_balloon(Background, GLuint, Player);
	void move_left(float);
	void drawBalloon(Background, GLuint, Player);
	void release_balloon(Player);
};

class TimeBomb{
public :
	
	TimeBomb();
	TimeBomb(float x, float y, float z);

	Object bomb;

	void create_bomb();
	void render_bomb(Background, GLuint);
	void move_left(float);
	float bomb_effect();
};

#endif