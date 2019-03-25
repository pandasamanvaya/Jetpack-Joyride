int drawRectangle(GLfloat shape[], int i, float l, float b);
int drawRectangle(GLfloat shape[], int i, float l, float b, float z);
void color_shape(GLfloat color_data[], int off, int len, const float color[]);
int create_regular_poly(GLfloat shape[], int len, int n, float r);
void create_triangle(GLfloat shape[], int i, float x[], float y[], float z[]);
void shift_shape(GLfloat shape[], int off, int len, float shift_x, float shift_y);