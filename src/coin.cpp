#include "coin.h"

Coin :: Coin(const float color[], float x, float y, float z)
{
	float r = 0.02;

	this -> coin.len = create_regular_poly(this -> coin.boundary, 0, 50, r);
	this -> coin.position = vec3(x, y, z);

	color_shape(this -> coin.color_data, 0, this -> coin.len, color);
}

void Coin :: create_coin() 
{
	glGenBuffers(1, &(this -> coin.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> coin.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this -> coin.boundary), this -> coin.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> coin.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> coin.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this -> coin.color_data), this -> coin.color_data, GL_STATIC_DRAW);

}

void Coin :: render_coin(Background bg, GLuint MatrixID) 
{
	mat4 transform = bg.position_object(this -> coin.position) * bg.project;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> coin.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> coin.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
		// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, (this -> coin.len)/3); 

	bg.disable();
}

void Coin :: move_left(float speed)
{
	if(this -> coin.position.x > -2.0)
		this -> coin.position.x -= speed;
}
void Coin :: set_position(GLfloat data[], float coord[])
{

}