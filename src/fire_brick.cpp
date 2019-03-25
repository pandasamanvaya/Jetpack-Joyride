#include "fire_brick.h"
Timer t20(1.0/10);

FireLine :: FireLine(float x, float y, float z)
{
	this -> fire.position = vec3(x, y, z);

	float len = 0.4;

	this -> fire.len = drawRectangle(this -> fire.boundary, 0, len, 0.02);
	int off = this -> fire.len;
	this -> fire.len = create_regular_poly(this -> fire.boundary, this -> fire.len, 50, 0.04);
	shift_shape(this -> fire.boundary , off, this-> fire.len, len/2, 0.0);
	off = this -> fire.len;
	this -> fire.len = create_regular_poly(this -> fire.boundary, this -> fire.len, 50, 0.04);
	shift_shape(this -> fire.boundary , off, this-> fire.len, -len/2, 0.0);

	//printf("%f %f\n", this -> fire.position.x, this -> fire.position.y);
	color_shape(this -> fire.color_data, 0, this -> fire.len, fire_red);

}

void FireLine :: create_block()
{
	glGenBuffers(1, &(this -> fire.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> fire.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->fire.boundary), this->fire.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> fire.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> fire.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->fire.color_data), this->fire.color_data, GL_STATIC_DRAW);

}

void FireLine :: render_block(Background bg, GLuint MatrixID)
{

	mat4 transform = bg.position_object(this -> fire.position) * bg.project;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> fire.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> fire.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glDrawArrays(GL_TRIANGLES, 0, (this -> fire.len)/3); 
	this -> oscillate();

	bg.disable();
}

void FireLine :: move_left(float speed)
{
	//printf("speed = %f\n", this -> fire.position.x);
	if(this -> fire.position.x > -2.0){
		this -> fire.position.x -= speed;
	}
}

void FireLine :: set_position(float x, float y, float z)
{
	this -> fire.position = vec3(x, y, z);
	//printf("line = %f\n", this -> fire.position.x);

}

void FireLine :: oscillate()
{
	float speed = 0.01;
	static int i = 0;
	if(this -> fire.position.y < 0.9 and i < 16){
		this -> fire.position.y += speed;
		i++;
	}
	else if(this -> fire.position.y > 0 and i < 32){
		this -> fire.position.y -= speed;
		i++;
	}
	else i = 0;
}


//Fire Beam Part
FireBeam :: FireBeam(float x, float y, float z)
{
	this -> fire.position = vec3(x, y, z);

	float line = 1.2;
	this -> fire.len = drawRectangle(this -> fire.boundary, 0, line, 0.07);

	float len = 0.08;
	float p1[] = {0.0, len, 0.0};
	float p2[] = {len, 0.0, 0.0};
	float p3[] = {0.0, -len, 0.0};
	float p4[] = {-len, 0.0, 0.0};

	int off = this -> fire.len;
	create_triangle(this -> fire.boundary, off, p1, p2, p3);
	this -> fire.len += 9;
	shift_shape(this -> fire.boundary , off, this-> fire.len, -line/2, 0.0);
	
	off = this -> fire.len;

	create_triangle(this -> fire.boundary, off, p1, p4, p3);
	this -> fire.len += 9;
	
	shift_shape(this -> fire.boundary , off, this-> fire.len, line/2, 0.0);
	//printf("%f %f\n", this -> fire.position.x, this -> fire.position.y);
	color_shape(this -> fire.color_data, 0, this -> fire.len, fire_red);
}

void FireBeam :: create_block()
{
	glGenBuffers(1, &(this -> fire.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> fire.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->fire.boundary), this->fire.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> fire.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> fire.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->fire.color_data), this->fire.color_data, GL_STATIC_DRAW);

}

void FireBeam :: render_block(Background bg, GLuint MatrixID)
{

	mat4 transform = bg.position_object(this -> fire.position) * bg.project;
	
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> fire.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> fire.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
		// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 6, 6); 
	if(t20.processTick())
		glDrawArrays(GL_TRIANGLES, 0, 6); 
	this -> move_up_down(this->dir);
	bg.disable();
}

void FireBeam :: move_up_down(int i)
{
	static float speed = 0.003;
	if(i > 0 and this -> fire.position.y < 1.2){
		//Move Up
		this -> fire.position.y += speed;
	}

	else if(i <= 0 and this -> fire.position.y > -1.2){
		//Move Down
		this -> fire.position.y -= speed;

	}
}

void FireBeam :: set_position(float x, float y, float z, int dir)
{
	this -> fire.position = vec3(x, y, z);
	this -> dir = dir;
}