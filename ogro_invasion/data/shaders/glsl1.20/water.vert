#version 120

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;

attribute vec3 a_Vertex;
attribute vec2 a_TexCoord0;

varying vec4 color;
varying vec2 texCoord0;

void main(void) 
{
	vec4 pos = modelview_matrix * vec4(a_Vertex, 1.0);
	
	color = vec4(0.8f, 0.8f, 1.0f, 0.95f);
	texCoord0 = a_TexCoord0;
	gl_Position = projection_matrix * pos;	
}
