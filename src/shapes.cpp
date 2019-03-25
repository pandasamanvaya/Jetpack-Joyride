#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

void shift_shape(GLfloat shape[], int off, int len, float shift_x, float shift_y)
{
	
	for(int i = off, j = off+1; i < len && j < len; i+=3, j+=3){
		shape[i] += shift_x;
		shape[j] += shift_y;
	}
}

void color_shape(GLfloat color_data[], int off, int len, const float color[])
{
	for(int i = off; i < len; i+=3){
		color_data[i] = color[0];
		color_data[i+1] = color[1];
		color_data[i+2] = color[2];
	}
}
void create_triangle(GLfloat shape[], int i, float x[], float y[], float z[])
{
	shape[i] = x[0];
	shape[i + 1] = x[1];
	shape[i + 2] = x[2];
	shape[i + 3] = y[0];
	shape[i + 4] = y[1];
	shape[i + 5] = y[2];
	shape[i + 6] = z[0];
	shape[i + 7] = z[1];
	shape[i + 8] = z[2];
}

int create_regular_poly(GLfloat shape[], int len, int n, float r)
{
	float theta = 360.0/n, x = 0.0, y = r;
	int i;
	
	for(i = len; i < 9*n + len; i += 9){
		float up_x = x * cos((3.1415926/180) * theta) - y * sin((3.1415926/180) * theta);
		float up_y = x * sin((3.1415926/180) * theta) + y * cos((3.1415926/180) * theta);

		float p1[] = {x, y, 0.0};
		float p2[] = {up_x, up_y, 0.0};
		float p3[] = {0.0, 0.0, 0.0};
		create_triangle(shape, i, p1, p2, p3);
		x = up_x; y = up_y;

	}
	//shift_shape(shape, len, 9*n, pos_x, pos_y);
	return i;
}

int drawRectangle(GLfloat shape[], int i, float l, float b)
{
	float p1[] = {-l/2, -b/2, 0.0};
	float p2[] = {-l/2, b/2, 0.0};
	float p3[] = {l/2, -b/2, 0.0};
	float p4[] = {l/2, b/2, 0.0};

	create_triangle(shape, i, p1, p2, p3);
	create_triangle(shape, i+9, p4, p3, p2);
	//shift_shape(shape, 0, 18, x, y);

	/*for(int i = 0; i < 18; i+=3)
		printf("%f %f %f\n", shape[i], shape[i+1], shape[i+2]);
*/	
	return (18);
}

int drawRectangle(GLfloat shape[], int i, float l, float b, float z)
{
	float p1[] = {-l/2, -b/2, z};
	float p2[] = {-l/2, b/2, z};
	float p3[] = {l/2, -b/2, z};
	float p4[] = {l/2, b/2, z};

	create_triangle(shape, i, p1, p2, p3);
	create_triangle(shape, i+9, p4, p3, p2);

	return 18;
}