#version 400 core 

//in vec3 vColour;			// Note: colour is smoothly interpolated (default)
in vec3 n;
in vec4 p;

out vec4 vOutputColour;

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

struct MaterialInfo
{
	vec3 Ma;
	vec3 Md;
	vec3 Ms;
	float shininess;
};

//uniform LightInfo light1; 
//uniform LightInfo light2;
uniform LightInfo light[8];
uniform MaterialInfo material1;

vec3 PhongModel(LightInfo light ,vec4 p, vec3 n)
{
	vec3 s = normalize(vec3(light.position - p));
	vec3 v = normalize(-p.xyz);
	vec3 r = reflect(-s, n);
	vec3 h = normalize(v + s);
	vec3 ambient = light.La * material1.Ma;
	float sDotN = max(dot(s, n), 0.0);
	vec3 diffuse = light.Ld * material1.Md * sDotN;
	vec3 specular = vec3(0.0);
	if (sDotN > 0.0)
		specular = light.Ls * material1.Ms * pow(max(dot(h, n), 0.0), material1.shininess);
	
	return ambient + diffuse + specular;

}

vec3 BlinnPhongSpotlightModel(LightInfo light, vec4 p, vec3 n)
{
	vec3 s = normalize(vec3(light.position - p));
	float angle = acos(dot(-s, light.direction));
	float cutoff = radians(clamp(light.cutoff, 0.0, 90.0));
	vec3 ambient = light.La * material1.Ma;
	if (angle < cutoff) 
	{
		float spotFactor = pow(dot(-s, light.direction), light.exponent);
		vec3 v = normalize(-p.xyz);
		vec3 h = normalize(v + s);
		float sDotN = max(dot(s, n), 0.0);
		vec3 diffuse = light.Ld * material1.Md * sDotN;
		vec3 specular = vec3(0.0);

		if (sDotN > 0.0)
		{
			specular = light.Ls * material1.Ms * pow(max(dot(h, n), 0.0), material1.shininess);
		}

		return ambient + spotFactor * (diffuse + specular);
	}

	else
	{
		return ambient;
	}
}

void main()
{	
	vec3 vColour = BlinnPhongSpotlightModel(light[0], p, normalize(n));
	vColour = vColour + BlinnPhongSpotlightModel(light[1], p, normalize(n));

	vOutputColour = vec4(vColour, 1);
}
