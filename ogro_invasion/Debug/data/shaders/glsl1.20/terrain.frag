#version 150

uniform sampler2D texture0;
uniform sampler1D texture1;

out vec4 color;
out vec2 texCoord0;
out float texCoord1;

out vec4 outColor;

void main(void) {
	outColor = color * texture(texture0, texCoord0.st) * texture(texture1, texCoord1);
}
