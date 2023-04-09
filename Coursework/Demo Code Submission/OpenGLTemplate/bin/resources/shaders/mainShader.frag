#version 400 core

in vec3 vColour;			// Interpolated colour using colour calculated in the vertex shader
in vec2 vTexCoord;			// Interpolated texture coordinate using texture coordinate from the vertex shader

out vec4 vOutputColour;		// The output colour

uniform sampler2D sampler0;  // The texture sampler

uniform samplerCube CubeMapTex;
uniform bool bUseTexture;    // A flag indicating if texture-mapping should be applied
uniform bool renderSkybox;
in vec3 worldPosition;

// Uniform variables for motion blur 
// CURRENTLY NOT WORKING SO COMMENTED
/*
uniform sampler2D sampler1;
uniform mat4 invMVP;
uniform mat4 prevMVP;
*/


void main()
{
	if (renderSkybox) 
	{
		vOutputColour = texture(CubeMapTex, worldPosition);
	} 

	else 
	{
		
		// Working out colours for motion blur
		// CURRENTLY NOT WORKING SO COMMENTED
		/*
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
		vec2 blurVec = (q.xy - vTexCoord)*5.0f;
		vec4 result = texture(sampler0, vTexCoord);
		int nSamples = 11;
		for (int i = 1; i < nSamples; i++) {
		vec2 offset = blurVec * (float(i) / float(nSamples - 1) - 0.5);
		result += texture(sampler0, vTexCoord + offset);
		}
		result /= float(nSamples);
		vOutputColour = result;
		*/


		// Get the texel colour from the texture sampler
		vec4 vTexColour = texture(sampler0, vTexCoord);	

		if (bUseTexture)
		{
			vOutputColour = vTexColour*vec4(vColour, 1.0f);	// Combine object colour and texture 
		}
		else
		{
			vOutputColour = vec4(vColour, 1.0f);	// Just use the colour instead
		}
	}
}
