#version 330 core

// Ouput data
out vec4 color1;

in vec2 texture1;
uniform sampler2D Rocket;
void main()
{

	// Output color = red 
	color1 = texture(Rocket, texture1);

}