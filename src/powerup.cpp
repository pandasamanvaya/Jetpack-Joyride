#include "powerup.h"

Timer t2(1/10.0);
float g = 0.002;

Shield :: Shield(float x, float y, float z)
{
	this -> cover.position = vec3(x, y, z);

	float r = 0.18;
	for(float theta = 0.0; theta < 360.0; theta++){
		float x = (r/2)*cos((3.1415926/180) * theta);
		float y = r*sin((3.1415926/180) * theta);

		int off = this -> cover.len;
		//printf("%d\n", off); 	
		this -> cover.len += drawRectangle(this->cover.boundary, off, 0.005, 0.005);
		shift_shape(this->cover.boundary, off, this->cover.len, x, y);
	}
	color_shape(this -> cover.color_data, 0, this -> cover.len, green);
}

void Shield :: create_shield()
{
	glGenBuffers(1, &(this -> cover.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> cover.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->cover.boundary), this->cover.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> cover.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> cover.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->cover.color_data), this->cover.color_data, GL_STATIC_DRAW);

}

void Shield :: render_shield(Background bg, GLuint MatrixID)
{
	mat4 transform = bg.position_object(this -> cover.position) * bg.project;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> cover.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> cover.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, (this -> cover.len)/3); 
	bg.disable();

	this -> move_on_screen();
}

bool up = false;
void Shield :: move_on_screen()
{
	float x_speed = 0.003, y_speed = 0.01;

	if(this->cover.position.y < 0.7 and !up){
		y_speed -= g;
		this->cover.position.y += y_speed;
	}
	else if(this->cover.position.y > -0.6){
		y_speed += g;
		this->cover.position.y -= y_speed;
		up = true;
	}
	else{
		up = false;
		y_speed = 0.01;
	}

	if(this->cover.position.x > -1.4)
		this->cover.position.x -= x_speed;
}

void Shield :: move_left(float speed)
{
	this -> cover.position.x -= speed;
}

void Shield :: set_position(float x, float y, float z)
{
	this -> cover.position = vec3(x, y, z);

}

//Heart

Heart :: Heart(float x, float y, float z)
{
	this -> life.position = vec3(x, y, z);
	float r = 0.05;

	float p1[] = {r/2, 0.0, 0.0};
	float p2[] = {-r/2, 0.0, 0.0};
	float p3[] = {0.0, -r, 0.0};

	this -> life.len = 9;
	create_triangle(this->life.boundary, 0, p1, p2, p3);
	int off = this -> life.len;

	this -> life.len = create_regular_poly(this->life.boundary, off, 50, r/3);
	shift_shape(this->life.boundary, off, this->life.len, r/4.5, r/4.5);

	off = this -> life.len;

	this -> life.len = create_regular_poly(this->life.boundary, off, 50, r/3);
	shift_shape(this->life.boundary, off, this->life.len, -r/4.5, r/4.5); 

	color_shape(this -> life.color_data, 0, this -> life.len, heart_red);
}

void Heart :: create_heart()
{
	glGenBuffers(1, &(this -> life.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> life.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->life.boundary), this->life.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> life.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> life.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->life.color_data), this->life.color_data, GL_STATIC_DRAW);

}

void Heart :: render_heart(Background bg, GLuint MatrixID)
{
	mat4 transform = bg.position_object(this -> life.position) * bg.project;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> life.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> life.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, (this -> life.len)/3); 

	this -> move_on_screen();
	bg.disable();

}

bool top = false;
void Heart :: move_on_screen()
{
	float x_speed = 0.003, y_speed = 0.01, g = 0.001;

	if(this->life.position.y < 0.8 and !top){
		y_speed -= g;
		this->life.position.y += y_speed;
	}
	else if(this->life.position.y > -0.7){
		y_speed += g;
		this->life.position.y -= y_speed;
		top = true;
	}
	else{
		top = false;
		y_speed = 0.01;
	}

	if(this->life.position.x > -1.4)
		this->life.position.x -= x_speed;
}

void Heart :: move_left(float speed)
{
	this -> life.position.x -= speed;
}

void Heart :: set_position(float x, float y, float z)
{
	this -> life.position = vec3(x, y, z);

}

//Water Balloon
WaterBalloon :: WaterBalloon(float x, float y, float z)
{
	this -> icon_position = vec3(x, y, z);

	float r = 0.02, s_x, s_y;
	
	for(int i = 0; i < 4; i++){
		int off = this -> icon_len;
		this -> icon_len = create_regular_poly(this->icon, off, 50, r);
	//	printf("%d\n", this->icon_len);
		if(i % 2)
			s_x = -r;
		else
			s_x = r;

		if(i > 1)
			s_y = r;
		else
			s_y = -r;
		shift_shape(this->icon, off, this->icon_len, s_x, s_y); 
	}

	color_shape(this->icon_color, 0, this->icon_len, blue);

	this -> water.len = create_regular_poly(this->water.boundary, 0, 20, r/2);
	color_shape(this->water.color_data, 0, this->water.len, blue);

}

void WaterBalloon:: create_balloon()
{
	glGenBuffers(1, &(this -> water.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> water.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->water.boundary), this->water.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> water.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> water.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->water.color_data), this->water.color_data, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> icon_vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> icon_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->icon), this->icon, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> icon_colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> icon_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->icon_color), this->icon_color, GL_STATIC_DRAW);

}

void WaterBalloon:: render_balloon(Background bg, GLuint MatrixID, Player player)
{
	mat4 transform = bg.position_object(this -> icon_position) * bg.project;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> icon_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> icon_colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, (this -> icon_len)/3); 

	bg.disable();

	this -> drawBalloon(bg, MatrixID, player);

}

void WaterBalloon :: move_left(float speed)
{
	this -> icon_position.x -= speed;
}

void WaterBalloon :: drawBalloon(Background bg, GLuint MatrixID, Player player)
{

	mat4 transform = bg.position_object(this->water.position) * bg.project;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> water.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> water.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, (this -> water.len)/3); 

	if(this -> press)
		this -> release_balloon(player);
	else
		this -> water.position = player.man.position;

	bg.disable();

}

bool fired = false;
void WaterBalloon :: release_balloon(Player player)
{
	float x_speed = 0.05;

	if(this->water.position.x < 1.1)
		this->water.position.x += x_speed;

	else{
		this -> press = false;
	}
}

//TimeBomb

TimeBomb :: TimeBomb(float x, float y, float z)
{
	this -> bomb.position = vec3(x, y, z);

	float r = 0.05;
	this -> bomb.len = create_regular_poly(this->bomb.boundary, 0, 50, r);
	int off = this -> bomb.len;

	this -> bomb.len = create_regular_poly(this->bomb.boundary, off, 4, r/4);
	shift_shape(this->bomb.boundary, off, this->bomb.len, 0, r/2);
	off = this -> bomb.len;

	this -> bomb.len = create_regular_poly(this->bomb.boundary, off, 4, r/4);
	shift_shape(this->bomb.boundary, off, this->bomb.len, r/3, r);

	color_shape(this->bomb.color_data, 0, this -> bomb.len, heart_red);
}

void TimeBomb :: create_bomb()
{
	glGenBuffers(1, &(this -> bomb.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> bomb.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->bomb.boundary), this->bomb.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> bomb.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> bomb.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->bomb.color_data), this->bomb.color_data, GL_STATIC_DRAW);

}

void TimeBomb :: render_bomb(Background bg, GLuint MatrixID)
{
	mat4 transform = bg.position_object(this -> bomb.position) * bg.project;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> bomb.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> bomb.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	if(!t2.processTick())
		glDrawArrays(GL_TRIANGLES, 0, (this -> bomb.len)/3); 

	bg.disable();

}

void TimeBomb :: move_left(float speed)
{
	this -> bomb.position.x -= speed;
}

float TimeBomb :: bomb_effect()
{
	return 0.005;
}
