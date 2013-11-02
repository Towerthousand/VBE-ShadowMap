#version 420

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 depthMVP;
uniform vec3 lightDir;

in vec3 a_position;
in vec3 a_normal;
in vec2 a_texCoord;

out vec2 vTexCoord;
out vec4 vShadowCoord;
out vec3 vNormal;
out vec3 lightDirection;

void main () {
	gl_Position = modelViewProjectionMatrix * vec4(a_position,1.0);
	vShadowCoord = depthMVP * vec4(a_position,1.0);
	vTexCoord = a_texCoord;
	lightDirection = vec4(viewMatrix*vec4(lightDir,0)).xyz;
	vNormal = vec4(viewMatrix * modelMatrix * vec4(a_normal,0.0f)).xyz;
}
