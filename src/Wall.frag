#version 330 core

// Ouput data
out vec4 color0;

in vec2 texture0;

uniform sampler2D Wall;

void main()
{

	// Output color = red 
	color0 = texture(Wall, texture0);

}