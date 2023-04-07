#version 400 core

out vec4 FragColour;
in vec2 vTexCoord;

uniform sampler2D screen;

void main()
{
	FragColour = vec4(vTexCoord + 1.0, 0.000, 1.0)/2.0;
}