#include "boomerang.h"

Boomerang :: Boomerang(float x, float y, float z)
{
	this -> boom.position = vec3(x, y, z);

	float len = 0.1;
	float p1[] = {len/4, 0.0, 0.0};
	float p2[] = {-len/4, 0.0, 0.0};
	float p3[] = {len, len, 0.0};
	float p4[] = {len, -len, 0.0};

	create_triangle(this -> boom.boundary, 0, p1, p2, p3);
	create_triangle(this -> boom.boundary, 9, p1, p2, p4);

	this -> boom.len = 18;

	color_shape(this -> boom.color_data, 0, this -> boom.len, black);
}

void Boomerang :: create_boom()
{
	glGenBuffers(1, &(this -> boom.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> boom.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->boom.boundary), this->boom.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> boom.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> boom.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->boom.color_data), this->boom.color_data, GL_STATIC_DRAW);
}

void Boomerang :: render_boom(Background bg, GLuint MatrixID, int angle)
{	
	//this -> boom.position = move_boom();
	mat4 transform = bg.position_object(this -> boom.position) * bg.project;
	transform = rotate(transform, radians((float)angle), vec3(0.0, 0.0, 1.0));
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> boom.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> boom.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
		
	glDrawArrays(GL_TRIANGLES, 0, 6); 
	this -> move_boom();
	bg.disable();
}

void Boomerang :: move_boom()
{
	static float left = 0.01, end = 1.4;
	if(this -> boom.position.x > -end and !out){
		this -> boom.position.x -= 2*left;
	}
	else if(this -> boom.position.x < end){
		this -> boom.position.y = this -> turn;
		this -> boom.position.x += left;
		this -> out = true;
	}
	//printf("out = %d %f\n", out, this -> boom.position.x );
}

void Boomerang :: set_position(float x, float y, float z)
{
	this -> boom.position = vec3(x, y, z);
	this -> turn = y - 0.4;
}