#version 330

uniform mat4 MVP;
uniform mat4 M;

attribute vec4 vPos;
attribute vec4 vColor;
attribute vec2 vTexCoord;
attribute vec4 vNormal;

out vec4 fPos;
out vec4 fColor;
out vec2 fTexCoord;
out vec4 fNormal;

void main()
{
	fPos = M * vPos;
	fColor = vColor;
	fTexCoord = vTexCoord;
	fNormal = normalize(inverse(transpose(M)) * vNormal);
	
	gl_Position = MVP * vPos;
}