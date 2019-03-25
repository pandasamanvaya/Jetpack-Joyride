#include "rocket.h"
#include "Image.h"
#include "shapes.h"

Rocket :: Rocket(float l, float b, float x_cntr, float y_cntr, float z_cntr)
{
	this -> rocket.len = drawRectangle(this->rocket.boundary, 0, l , b);

}
void Rocket :: create_rocket(const char *file, GLuint programID)
{
	this -> img = load_image(file);
	this -> ID = glGetUniformLocation(programID, "tex1");
	this -> bind_rocket();
	this -> bind_rocket_texture();

	//glDeleteVertexArrays(1, &vao);
/*	glDeleteBuffers(1, &(this -> rocket.vertexbuffer));
	glDeleteBuffers(1, &(this -> rocket.texbuffer));
*/}
void Rocket :: bind_rocket()
{
	glGenBuffers(1, &(this -> rocket.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> rocket.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->rocket.boundary), this->rocket.boundary, GL_STATIC_DRAW);
	
}

void Rocket :: bind_rocket_texture()
{	
	static GLfloat rocket_text_cord[] = {
		0.07, 0.0,
		0.07, 1.0,
		1.0, 0.0,
		1.0, 1.0,
		1.0, 0.0,
		0.07, 1.0
	};

	glGenBuffers(1, &(this -> texbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> texbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rocket_text_cord), rocket_text_cord, GL_STATIC_DRAW);
	
}

void Rocket :: render_rocket(Background bg, GLuint object, int i)
{
	glBindBuffer(GL_ARRAY_BUFFER, this -> rocket.vertexbuffer);
	bg.render_object();

	glActiveTexture(GL_TEXTURE0 + i);

	glBindBuffer(GL_ARRAY_BUFFER, this -> texbuffer);
	bg.render_texture(object);
	glUniform1i(this -> ID, i);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	bg.disable();

}