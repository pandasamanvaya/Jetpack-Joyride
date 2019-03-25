#include "main.h"
#include "background.h"
#include "object.h"
#include "Image.h"
#include "shapes.h"

class Wall{
public:
	Wall(){}
	Wall(float l, float b, float x_cntr, float y_cntr, float z_cntr);
	Object wall;
	GLuint texbuffer;
	GLuint img;
	GLuint ID;

	void create_wall(const char*, GLuint);
	void bind_wall();
	void bind_wall_texture();
	void render_wall(Background, GLuint, GLuint);
	mat4 position_wall();
	void set_position(float, float, float);
	void move_left(float);
	
};