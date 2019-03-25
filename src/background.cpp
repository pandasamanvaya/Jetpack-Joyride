#include "background.h"

GLFWwindow* Background :: create_window(int height, int width)
{
	if(!glfwInit()){
		fprintf(stderr, "Unable to initialize glfw\n");
		exit(GLFW_FAIL);
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(height, width, "Jetpack Joyride", NULL, NULL);

	if(window == NULL){
		printf("Window not created\n");
		exit(3);
	}
	glfwMakeContextCurrent(window);
	
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		exit(GLEW_FAIL);
	}
	return window;
}

void Background :: render_object()
{
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);
}
void Background :: render_texture(GLuint object)
{
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(1);

	glBindTexture(GL_TEXTURE_2D, object);

}

void Background :: disable()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

mat4 Background :: position_object(vec3 position)
{
	mat4 Model      = mat4(1.0f);

	mat4 Translate = translate(mat4(1.0f), position); 
	mat4 transform  = Model * Translate; 

	return transform;
}

void Background :: reshapeWindow(GLFWwindow *window, int width, int height, float zoom)
{
    int fbwidth = width, fbheight = height;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

    glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);
    this -> project = ortho(-zoom, zoom, -zoom, zoom);

}
