#version 420

uniform sampler2D sampler;
uniform sampler2D depthBuffer;

in vec2 vTexCoord;
in vec4 vShadowCoord;
in vec3 vNormal;
in vec3 lightDirection;

out vec4 color;

void main() {

	// Light emission properties
	vec3 lightColor = vec3(1,1,1);
	float lightPower = 0.2f;

	// Material properties
	vec3 MaterialDiffuseColor = texture2D(sampler,vTexCoord).rgb;
	vec3 MaterialAmbientColor = vec3(0.8,0.8,0.8) * MaterialDiffuseColor;

	float cosTheta = max(dot(normalize(vNormal), normalize(lightDirection)), 0.0);

	float bias = 0.005*tan(acos(cosTheta));
	bias = clamp(bias, 0.0f,0.01f);

	float visibility = 1.0;
	if ( texture2D( depthBuffer, vShadowCoord.xy).z <  vShadowCoord.z-bias)
		visibility = 0.0;
	vec3 materialColor = texture2D(sampler,vTexCoord).xyz;
	color = vec4(MaterialAmbientColor +
				 lightColor*cosTheta*visibility*lightPower,1.0f);
}
