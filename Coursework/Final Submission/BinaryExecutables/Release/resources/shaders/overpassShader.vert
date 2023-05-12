#version 400 core

// The overpass shaders attempt to implment a tesselation shader but do NOT currently work

layout (location = 0 ) in vec3 VertexPosition;
layout (location = 1) in vec2 inCoord;
//layout (location = 2) in vec3 inNormal;
//layout (location = 3) in vec3 inColour;

out vec2 vTexCoord;	// Texture coordinate
//out vec3 vCol; // colour

void main()
{
    gl_Position = vec4(VertexPosition, 1.0);

    // get the colour from the vbo
	//vCol = inColour;

	// Pass through the texture coordinate
	vTexCoord = inCoord;
}