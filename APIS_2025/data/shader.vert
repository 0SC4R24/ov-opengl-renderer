#version 330

uniform mat4 MVP;
uniform mat4 M;

attribute vec4 vPos;
attribute vec4 vColor;
attribute vec2 vTexCoord;
attribute vec4 vNormal;

out vec3 fPos;
out vec4 fColor;
out vec2 fTexCoord;
out vec3 fNormal;

void main()
{
	vec4 worldPos = M * vPos;
	fPos = worldPos.xyz;

	mat3 normalMatrix = transpose(inverse(mat3(M)));
	fNormal = normalize(normalMatrix * vNormal.xyz);

	fColor = vColor;
	fTexCoord = vTexCoord;
	
	gl_Position = MVP * vPos;
}