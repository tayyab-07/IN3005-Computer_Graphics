#version 400 core

in vec3 vEyeNorm;
in vec4 vEyePosition;
in vec2 vTexCoord;
in vec3 vCol;

out vec4 vOutputColour;		// The output colour

uniform sampler2D sampler0;  // The texture sampler
uniform bool bUseTexture;    // A flag indicating if texture-mapping should be applied

// Structure holding light information:  its position as well as ambient, diffuse, and specular colours
// structure also holds direction, exponent and cutoff for the spotlights
struct LightInfo
{
	vec4 position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
	vec3 direction;
	float exponent;
	float cutoff;
};

// Structure holding material information:  its ambient, diffuse, and specular colours, and shininess
// Ive only added the shininess on this particular occasion because, the colours are stored in the vbo
struct MaterialInfo
{
	vec3 Ma;
	vec3 Md;
	vec3 Ms;
	float shininess;
};

// Lights and materials passed in as uniform variables from client programme
// lights stored in an array
uniform LightInfo light[3]; 
uniform MaterialInfo material1;

// This function implements the Phong shading model
// This function is called when a tunnel is not lit by a spotlight
vec3 PhongModel(LightInfo light1, vec4 vEyePosition, vec3 vEyeNorm)
{
	vec3 s = normalize(vec3(light1.position - vEyePosition));
	vec3 v = normalize(-vEyePosition.xyz);
	vec3 r = reflect(-s, vEyeNorm);
	vec3 n = vEyeNorm;
	vec3 ambient = light1.La * vCol * material1.Ma;
	float sDotN = max(dot(s, n), 0.0f);
	vec3 diffuse = light1.Ld * vCol * material1.Md * sDotN;
	vec3 specular = vec3(0.0f);
	float eps = 0.000001f; // add eps to shininess below -- pow not defined if second argument is 0 (as described in GLSL documentation)

	if (sDotN > 0.0f) 
	{
		specular = light1.Ls * vCol * material1.Ms * pow(max(dot(r, v), 0.0f), material1.shininess + eps);
	}	

	return ambient + diffuse + specular;
}

// function to call the phong model from the Blinn phong model
vec3 passToPhong()
{
	return PhongModel(light[0], vEyePosition, vEyeNorm);
}

vec3 BlinnPhongSpotlightModel(LightInfo light, vec4 vEyePosition, vec3 vEyeNorm)
{
	vec3 s = normalize(vec3(light.position - vEyePosition));
	float angle = acos(dot(-s, light.direction));
	float cutoff = radians(clamp(light.cutoff, 0.0, 180.0));
	vec3 ambient = light.La * vCol * material1.Ma;
	if (angle < cutoff) 
	{
		float spotFactor = pow(dot(-s, light.direction), light.exponent);
		vec3 v = normalize(-vEyePosition.xyz);
		vec3 h = normalize(v + s);
		float sDotN = max(dot(s, vEyeNorm), 0.0);
		vec3 diffuse = light.Ld * vCol * material1.Md * sDotN;
		vec3 specular = vec3(0.0);

		if (sDotN > 0.0)
		{
			specular = light.Ls * vCol * material1.Ms * pow(max(dot(h, vEyeNorm), 0.0), material1.shininess);
		}

		return ambient + spotFactor * (diffuse + specular);
	}

	// call the phong model through the passToPhong model
	// this is done to correctly colour parts of the tunnel that are not lit by the spotlight
	else
	{
		return passToPhong();
	}
}

void main()
{
	// working out the colour based on the lights in the scene
	// light[0] = world lught, other lights = car headlammps
	vec3 vColour = BlinnPhongSpotlightModel(light[0], vEyePosition, normalize(vEyeNorm));
	vColour = vColour + BlinnPhongSpotlightModel(light[1], vEyePosition, normalize(vEyeNorm));
	vColour = vColour + BlinnPhongSpotlightModel(light[2], vEyePosition, normalize(vEyeNorm));

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