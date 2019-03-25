#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 text1;

out vec2 texture1;
uniform mat4 tex1;

void main(){

    gl_Position = tex1 * vec4(vertexPosition_modelspace,1);
    texture1 = text1;
}

