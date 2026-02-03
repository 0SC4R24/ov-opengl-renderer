#version 330

uniform sampler2D textureColor;
uniform bool useColorText;

in vec4 fColor;
in vec2 fTexCoord;

void main()
{
	vec4 tColor = vec4(0,0,0,0);
	if (useColorText)
	{
		tColor = texture(textureColor, fTexCoord);
	}

	gl_FragColor = fColor + tColor;
}