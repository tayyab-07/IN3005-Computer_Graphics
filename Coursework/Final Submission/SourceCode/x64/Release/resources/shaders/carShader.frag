#version 400

// This shader attempts to implement a motion blur but was unsuccessful

in vec2 vTexCoord;
out vec4 vOutputColour;

uniform sampler2D sampler0; // used to access the rendered image from pass 1
uniform sampler2D sampler1; // used to access the depth buffer

uniform mat4 invMVP;
uniform mat4 prevMVP;

void main()
{
	// Unproject the point to 3D using the current modelview and projection matrix
	float p_depth = texture(sampler1, vTexCoord).r;
	vec2 p_ndc = vTexCoord.xy * 2.0f - 1.0f;
	vec4 p3d = invMVP * vec4(p_ndc, p_depth, 1.0);
	p3d = p3d / p3d.w;

	// Project the point using the previous frame's modelview and projection matrix
	vec4 q = prevMVP * p3d;
	q.xyz /= q.w; // normalised device coordinates
	q.xy = q.xy * 0.5 + vec2(0.5); // texture coordinates

	// Construct the blur vector (scaled for extra blur)
	vec2 blurVec = (q.xy - vTexCoord)*500.0f;
	vec4 result = texture(sampler0, vTexCoord);
	int nSamples = 11;

	for (int i = 1; i < nSamples; i++) 
	{
		vec2 offset = blurVec * (float(i) / float(nSamples - 1) - 0.5);
		result += texture(sampler0, vTexCoord + offset);
	}

	result /= float(nSamples);
	vOutputColour = result;
}