#include "magnet.h"

Magnet :: Magnet(float x, float y, float z)
{
	this -> magnet.position = vec3(x, y, z);;

	float r = 0.2, t = 0.05;
	
	printf("%d\n", this->magnet.len);
	this -> magnet.len  += drawRectangle(this->magnet.boundary, 0, t, 0.2);
	shift_shape(this->magnet.boundary, 0, this->magnet.len, t, 0.08);
	int off = this -> magnet.len;
	this -> magnet.len  += drawRectangle(this->magnet.boundary, off, t, 0.2);
	shift_shape(this->magnet.boundary, off, this->magnet.len, -t+0.001, 0.08);
	
	/*this -> magnet.len = create_regular_poly(this->magnet.boundary, off, 50, r);
	off = this -> magnet.len;

	this -> magnet.len = create_regular_poly(this->magnet.boundary, off, 50, r);
	shift_shape(this->magnet.boundary, off, this->magnet.len, r/2, -r/4);

	off = this -> magnet.len;
	this -> magnet.len = create_regular_poly(this->magnet.boundary, off, 50, r);
	shift_shape(this->magnet.boundary, off, this->magnet.len, -r/2, -r/4);
	
	off = this -> magnet.len;
*/
	for(float theta = 60.0; theta < 120.0; theta++){
		float x = (r/2)*cos((3.1415926/180) * theta);
		float y = r*sin((3.1415926/180) * theta);

		off = this -> magnet.len;
		//printf("%d\n", off); 	
		this -> magnet.len += drawRectangle(this->magnet.boundary, off, t, t);
		shift_shape(this->magnet.boundary, off, this->magnet.len, x, y);
	}
	color_shape(this->magnet.color_data, 0, this -> magnet.len, black);

}

void Magnet :: create_magnet()
{
	glGenBuffers(1, &(this -> magnet.vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> magnet.vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this -> magnet.boundary), this -> magnet.boundary, GL_STATIC_DRAW);

	glGenBuffers(1, &(this -> magnet.colorbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, this -> magnet.colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this -> magnet.color_data), this -> magnet.color_data, GL_STATIC_DRAW);

}

void Magnet :: render_magnet(Background bg, GLuint MatrixID)
{
	mat4 transform = bg.position_object(this -> magnet.position) * bg.project;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this -> magnet.vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this -> magnet.colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
		// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, (this -> magnet.len)/3); 

	bg.disable();
}

void Magnet :: move_left(float speed)
{
	this -> magnet.position.x -= speed;
}

