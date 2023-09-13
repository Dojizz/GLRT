#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

void main()
{
	vec2 ScreenPos = vec2(FragPos[0], FragPos[1]);
	if (sqrt(ScreenPos[0] * ScreenPos[0] + 
		ScreenPos[1] * ScreenPos[1]) <= 0.5f)
		FragColor = vec4(1.f);
	else
		FragColor = vec4(vec3(0.f), 1.f);
}