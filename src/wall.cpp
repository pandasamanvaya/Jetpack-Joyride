#include "wall.h"

Wall :: Wall(float l, float b, float x_cntr, float y_cntr, float z_cntr)
{
	this -> wall.len = drawRectangle(this->wall.boundary, 0, l , b);
	this -> wall.position = vec3(x_cntr, y_cntr, z_cntr);

}
void Wall :: create_wall(const char *file, GLuint programID)
{
	this -> img = load_image(file);
	this -> ID = glGetUniformLocation(programID, "tex0");
	this -> bind_wall();
	this -> bind_wall_texture();

}
void Wall :: bind_wall()
{
	glGenBuffers(1, &(this -> wall.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> wall.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->wall.boundary), this->wall.boundary, GL_STATIC_DRAW);
	
}

void Wall :: bind_wall_texture()
{	
	static GLfloat wall_text_cord[] = {
		0.0, 0.0,
		0.0, 1.0,
		1.0, 0.0,
		1.0, 1.0,
		1.0, 0.0,
		0.0, 1.0
	};

	glGenBuffers(1, &(this -> texbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wall_text_cord), wall_text_cord, GL_STATIC_DRAW);
	
}

void Wall :: set_position(float x, float y, float z)
{
	this -> wall.position = vec3(x, y, z);

}

void Wall :: move_left(float speed)
{
	this -> wall.position.x -= speed;

}

void Wall :: render_wall(Background bg, GLuint object, GLuint MatrixID)
{
	mat4 transform = bg.position_object(this -> wall.position) * bg.project;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, this -> wall.vertexbuffer);
	bg.render_object();

	glActiveTexture(GL_TEXTURE0);

	glBindBuffer(GL_ARRAY_BUFFER, this -> texbuffer);
	bg.render_texture(object);
	glUniform1i(this -> ID, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	bg.disable();
}