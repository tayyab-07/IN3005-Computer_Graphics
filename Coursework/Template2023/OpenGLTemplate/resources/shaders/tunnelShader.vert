#version 400 core

// Structure for matrices
uniform struct Matrices
{
	mat4 projMatrix;
	mat4 modelViewMatrix; 
	mat3 normalMatrix;
} matrices;
 
// Layout of vertex attributes in VBO
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inCoord;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec3 inColour;

// outputs to fragment shader
out vec3 vEyeNorm; // Normal of point in eye coords
out vec4 vEyePosition; // position of point in eye coords
out vec2 vTexCoord;	// Texture coordinate
out vec3 vCol; // colour

// This is the entry point into the vertex shader
void main()
{	
	// Transform the vertex spatial position using 
	gl_Position = matrices.projMatrix * matrices.modelViewMatrix * vec4(inPosition, 1.0f);
	
	// Get the vertex normal and vertex position in eye coordinates
	vEyeNorm = normalize(matrices.normalMatrix * inNormal);
	vEyePosition = matrices.modelViewMatrix * vec4(inPosition, 1.0f);

	// get the colour from the vbo
	vCol = inColour;

	// Pass through the texture coordinate
	vTexCoord = inCoord;
}


	