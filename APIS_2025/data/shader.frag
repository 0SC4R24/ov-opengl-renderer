#version 330

struct light_t 
{
	vec4 position;
	vec4 color;
	vec4 direction;
	int type;
	bool enabled;
};

struct material_t
{
	int shiny;
};

uniform light_t light;
uniform material_t material;

uniform vec4 eyePos;
uniform sampler2D textureColor;
uniform bool useColorText;

in vec4 fPos;
in vec4 fColor;
in vec2 fTexCoord;
in vec4 fNormal;

vec4 calculateColor(light_t light)
{
	vec4 finalColor = fColor;
	
	if (useColorText)
	{
		finalColor = fColor * texture(textureColor, fTexCoord);
	}
	
	if (light.enabled)
	{
		float ambiental = 0.2f;
		float diffuse = 1;
		float specular = 1;
		
		vec3 L = vec3(0, 0, 0);
		vec3 N = fNormal.xyz;
		
		if (light.type == 0) L = light.position.xyz - fPos.xyz;
		if (light.type == 1) L = light.direction.xyz;
		
		L = normalize(L);
		N = normalize(N);
		diffuse = max(dot(L, N), 0.0f);
		
		vec3 R = normalize(reflect(L, N));
		vec3 V = normalize(fPos.xyz - eyePos.xyz);
		specular = pow(max(dot(R, V), 0), material.shiny);
		
		finalColor = finalColor * ((ambiental + diffuse + specular) * light.color);
	}
	
	return finalColor;
}

void main()
{
	gl_FragColor = calculateColor(light);
}