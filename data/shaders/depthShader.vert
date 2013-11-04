#version 420 core

uniform mat4 modelViewProjectionMatrix;

in vec3 a_position;

void main(void) {
	gl_Position = modelViewProjectionMatrix * vec4(a_position,1.0);
}
