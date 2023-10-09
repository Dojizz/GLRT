#version 330
in vec2 TexCoords;
uniform sampler2D tex;

out vec4 FragColor;

void main(){
	FragColor = texture(tex, TexCoords);
}