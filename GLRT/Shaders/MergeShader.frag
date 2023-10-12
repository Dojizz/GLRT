#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D pres_tex;
uniform sampler2D hist_tex;
uniform int loop_num;

void main() {
	float pres_w = 1.f / loop_num;
	float hist_w = 1.f - pres_w;

	FragColor = pres_w * texture(pres_tex, TexCoords) + hist_w * texture(hist_tex, TexCoords);
}