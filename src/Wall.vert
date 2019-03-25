#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 text0;

out vec2 texture0;
uniform mat4 tex0;

void main(){

    gl_Position = tex0 * vec4(vertexPosition_modelspace,1);
    texture0 = text0;
}

