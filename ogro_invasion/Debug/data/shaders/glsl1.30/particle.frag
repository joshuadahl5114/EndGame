#version 150

uniform sampler2D texture0;

in vec4 color;
out vec4 outColor;

void main(void) {
	//Sample the texture
	outColor = texture(texture0, gl_PointCoord) * color;
}
