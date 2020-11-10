#version 150

uniform sampler2D texture0;

out vec2 texCoord0;

void main(void) {
	//Sample the texture
	gl_FragColor = texture2D(texture0, texCoord0.st);	
}
