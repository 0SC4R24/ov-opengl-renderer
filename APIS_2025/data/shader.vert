#version 330

uniform mat4 MVP;
uniform mat4 M;

attribute vec4 vPos;
attribute vec4 vColor;

out vec4 fColor;

void main()
{
	//gl_Position = MVP * vPos;
	gl_Position = M * vPos;

	fColor = vColor;
}
