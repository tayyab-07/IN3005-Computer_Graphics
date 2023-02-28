#version 400 core

in vec3 vColour;		// Note: colour is smoothly interpolated (default)
in float fIntensity;
out vec4 vOutputColour;

void main()
{	
	//vOutputColour = vec4(vColour, 1.0);
	vOutputColour = vec4(fIntensity);

}
