#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

uint wseed;
float randcore(uint seed) {
	seed = (seed ^ uint(61)) ^ (seed >> uint(16));
	seed *= uint(9);
	seed = seed ^ (seed >> uint(4));
	seed *= uint(0x27d4eb2d);
	wseed = seed ^ (seed >> uint(15));
	return float(wseed) * (1.0 /  4294967296.0);
}

float rand() {
	return randcore(wseed);
}

void main()
{
	wseed = uint(float(69557857) * (TexCoords.x * TexCoords.y));
	vec2 ScreenPos = vec2(FragPos[0], FragPos[1]);
	if (distance(vec2(FragPos[0], FragPos[1]), vec2(0.f, 0.f)) < 0.4)
		FragColor = vec4(rand(), rand(), rand(), 1.f);
	else
		FragColor = vec4(vec3(0.f), 1.f);
}