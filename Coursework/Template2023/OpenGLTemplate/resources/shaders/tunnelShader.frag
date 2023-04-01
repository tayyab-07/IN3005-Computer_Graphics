#version 400 core

in vec3 vEyeNorm;
in vec4 vEyePosition;
in vec2 vTexCoord;
in vec3 vCol;

out vec4 vOutputColour;		// The output colour

uniform sampler2D sampler0;  // The texture sampler
uniform bool bUseTexture;    // A flag indicating if texture-mapping should be applied

// Structure holding light information:  its position as well as ambient, diffuse, and specular colours
struct LightInfo
{
	vec4 position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};

// Structure holding material information:  its ambient, diffuse, and specular colours, and shininess
// Ive only added the shininess on this particular occasion because, the colours are stored in the vbo
struct MaterialInfo
{
	float shininess;
};

// Lights and materials passed in as uniform variables from client programme
uniform LightInfo light1; 
uniform MaterialInfo material1;

// This function implements the Phong shading model
vec3 PhongModel(vec4 eyePosition, vec3 eyeNorm)
{
	vec3 s = normalize(vec3(light1.position - eyePosition));
	vec3 v = normalize(-eyePosition.xyz);
	vec3 r = reflect(-s, eyeNorm);
	vec3 n = eyeNorm;
	vec3 ambient = light1.La * vCol;
	float sDotN = max(dot(s, n), 0.0f);
	vec3 diffuse = light1.Ld * vCol * sDotN;
	vec3 specular = vec3(0.0f);
	float eps = 0.000001f; // add eps to shininess below -- pow not defined if second argument is 0 (as described in GLSL documentation)

	if (sDotN > 0.0f) 
	{
		specular = light1.Ls * vCol * pow(max(dot(r, v), 0.0f), material1.shininess + eps);
	}	

	return ambient + diffuse + specular;
}

void main()
{
	vec3 vColour = PhongModel(vEyePosition, normalize(vEyeNorm));

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
