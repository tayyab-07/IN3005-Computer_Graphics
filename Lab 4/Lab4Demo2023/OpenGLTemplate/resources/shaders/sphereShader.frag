#version 400 core

in vec3 vColour;		// Note: colour is smoothly interpolated (default)
in float fIntensity;
out vec4 vOutputColour;

void main()
{	
	//vOutputColour = vec4(vColour, 0.5);

	
	if (fIntensity < 0.5)
	{
		vOutputColour = vec4(0,0.3,0,0.5);
	}

	if (fIntensity > 0.5 && fIntensity < 0.75)
	{
		vOutputColour = vec4(0,0.6,0,0.5);
	}

	if (fIntensity > 0.75)
	{
		vOutputColour = vec4(0,0.9,0,0.5);
	}
	
	
	
}
