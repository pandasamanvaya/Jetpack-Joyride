#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexcolor;

uniform mat4 tex1;
out vec3 fragColor;

void main(){

	fragColor = vertexcolor;
	
    gl_Position = tex1 * vec4(vertexPosition_modelspace,1);

}

