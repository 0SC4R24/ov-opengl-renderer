#version 330

struct light_t 
{
	vec4 position;
	vec4 color;
	vec4 direction;
	int type;
	float linearAttenuation;
	bool enabled;
};

struct material_t
{
	int shiny;
};

uniform light_t lights[8];
uniform int activeLights;
uniform material_t material;

uniform float ambiental;

uniform vec4 eyePos;
uniform sampler2D textureColor;
uniform bool useColorText;

in vec3 fPos;
in vec4 fColor;
in vec2 fTexCoord;
in vec3 fNormal;

void main()
{
	vec4 finalColor = fColor;

	if (useColorText)
	{
		finalColor = fColor * texture(textureColor, fTexCoord);
	}

	vec3 N = normalize(fNormal);
	vec3 V = normalize(eyePos.xyz - fPos);

	vec3 lighting = vec3(ambiental);

	for (int i = 0; i < activeLights; i++)
	{
		light_t light = lights[i];
		if (!lights[i].enabled) continue;

		vec3 L;
		float attenuation = 1.0;
		if (light.type == 0) // Point
		{
			attenuation = 1 / (light.linearAttenuation);
			L = normalize(light.position.xyz - fPos);
		}
		else if (light.type == 1) // Directional
		{
			L = normalize(-light.direction.xyz);
		}

		float diffuse = max(dot(N, L), 0.0) * attenuation;
		vec3 R = reflect(-L, N);
		float specular = 0.0;
		if (diffuse > 0.0)
		{
			float shin = max(material.shiny, 1);
			specular = pow(max(dot(R, V), 0.0), shin) * attenuation;
		}

		vec3 lightCol = light.color.rgb;
		lighting += (diffuse + specular) * lightCol;
	}

	vec3 finalRGB = finalColor.rgb * lighting;
	gl_FragColor = vec4(finalRGB, finalColor.a);
}