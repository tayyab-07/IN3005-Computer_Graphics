#version 400 core

layout( triangles, equal_spacing, ccw ) in;

in vec2 Tex[];
out vec2 vTexCoord;

void main () 
{
	
	// barycentric coordinates
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    float w = gl_TessCoord.z;
    // barycentric interpolation
    vec2 texCoord = u * Tex[0] + v * Tex[1] + w * Tex[2];
    vec4 pos0 = gl_in[0].gl_Position;
    vec4 pos1 = gl_in[1].gl_Position;
    vec4 pos2 = gl_in[2].gl_Position;
    // barycentric interpolation
    vec4 pos = u * pos0 + v * pos1 + w * pos2;

    gl_Position = pos;
    vTexCoord = texCoord;

}
