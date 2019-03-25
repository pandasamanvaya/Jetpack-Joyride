#include "background.h"
#include "object.h"

class Rocket{
public:
	Rocket(){}
	Rocket(float l, float b, float x_cntr, float y_cntr, float z_cntr);
	Object rocket;
	GLuint texbuffer;
	GLuint img;
	GLuint ID;

	void create_rocket(const char*, GLuint);
	void bind_rocket();
	void bind_rocket_texture();
	void render_rocket(Background, GLuint, int);
};