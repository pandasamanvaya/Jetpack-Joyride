#include "player.h"
Timer t1(1.0);

Player :: Player(float x, float y, float z)
{
	this -> man.position = vec3(x, y, z);
	float height = 0.2, wid = 0.1, r = wid/2;
	//Body
	this -> man.len = drawRectangle(this -> man.boundary, 0, wid, height);
	int off = this -> man.len;
	//Head
	this -> man.len = create_regular_poly(this -> man.boundary, off, 50, r);
	shift_shape(this -> man.boundary, off, this->man.len, 0.0, height/2 + r);
	off = this -> man.len;
	//Left Leg
	this -> man.len = create_regular_poly(this -> man.boundary, off, 3, r/2);
	shift_shape(this -> man.boundary, off, this->man.len, -wid/4, -(height/2 + r/4));

	off = this -> man.len;
	//Right Leg
	this -> man.len = create_regular_poly(this -> man.boundary, off, 3, r/2);
	shift_shape(this -> man.boundary, off, this->man.len, wid/4, -(height/2 + r/4));
	
	color_shape(this->man.color_data, 0, this->man.len, brown);

}

void Player :: create_player()
{
	glGenBuffers(1, &(this -> man.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> man.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->man.boundary), this->man.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> man.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> man.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->man.color_data), this->man.color_data, GL_STATIC_DRAW);

}

void Player :: render_player(Background bg, GLuint MatrixID)
{
	mat4 transform = bg.position_object(this -> man.position) * bg.project;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> man.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> man.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glDrawArrays(GL_TRIANGLES, 0, (this -> man.len)/3); 
	bg.disable();

}

void Player :: jump(float speed)
{
	if(this -> man.position.y < 0.65)
		this -> man.position.y += speed;
}

void Player :: fall(float speed)
{
	if(this -> man.position.y > -0.6)
		this -> man.position.y -= speed/3.0;
}

void Player :: change_color(const float color[])
{
	color_shape(this->man.color_data, 0, this -> man.len, color);
	this -> create_player();
}