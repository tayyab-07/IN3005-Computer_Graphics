#version 400 core

// The tree shaders implenet Instanced Rendering

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

// outputs to fragment shader
out vec3 vEyeNorm; // Normal of point in eye coords
out vec4 vEyePosition; // position of point in eye coords
out vec2 vTexCoord;	// Texture coordinate

// This is the entry point into the vertex shader
void main()
{	
	// using gl_InstanceID with mod and div to set organisation of the trees
	// shift is multiplied by 6 to set the apcing between the trees
	// number of instancers passed in from TreeMesh.cpp
	float x = gl_InstanceID % 6;
	float z = gl_InstanceID / 6;
	vec3 shift = 6 * vec3(x, 0, z);
	// Transform the vertex spatial position using 
	gl_Position = matrices.projMatrix * matrices.modelViewMatrix * vec4(inPosition + shift, 1.0f);
	
	// Get the vertex normal and vertex position in eye coordinates
	vEyeNorm = normalize(matrices.normalMatrix * inNormal);
	vEyePosition = matrices.modelViewMatrix * vec4(inPosition, 1.0f);

	// Pass through the texture coordinate
	vTexCoord = inCoord;
}