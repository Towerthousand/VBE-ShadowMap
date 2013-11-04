#version 420 core

uniform sampler2D sampler;
uniform sampler2DShadow depthBuffer;

in vec2 vTexCoord;
in vec4 vShadowCoord;
in vec3 vNormalVector;
in vec3 vLightVector;
in vec3 vEyeVector;

out vec4 color;

vec2 poissonDisk[16] = {
	vec2( -0.94201624, -0.39906216 ),
	vec2( 0.94558609, -0.76890725 ),
	vec2( -0.094184101, -0.92938870 ),
	vec2( 0.34495938, 0.29387760 ),
	vec2( -0.91588581, 0.45771432 ),
	vec2( -0.81544232, -0.87912464 ),
	vec2( -0.38277543, 0.27676845 ),
	vec2( 0.97484398, 0.75648379 ),
	vec2( 0.44323325, -0.97511554 ),
	vec2( 0.53742981, -0.47373420 ),
	vec2( -0.26496911, -0.41893023 ),
	vec2( 0.79197514, 0.19090188 ),
	vec2( -0.24188840, 0.99706507 ),
	vec2( -0.81409955, 0.91437590 ),
	vec2( 0.19984126, 0.78641367 ),
	vec2( 0.14383161, -0.14100790 )
};

void main() {
	// Sun light properties
	vec3 sunLightColor = vec3(1.0f);
	float sunLightPower = 0.75f;

	// Ambient light properties
	vec3 ambientLightColor = vec3(1.0f);
	float ambientLightPower = 1.0f-sunLightPower;

	// material properties
	vec3 matDiffuseColor = texture(sampler,vTexCoord).xyz;
	vec3 matSpecularColor = vec3(0.5f);

	//light calculations
	vec3 E = normalize(vEyeVector);
	vec3 R = reflect(-normalize(vLightVector),normalize(vNormalVector));
	float cosAlpha = clamp(dot(E,R),0.0f,1.0f);
	float cosTheta = max(dot(normalize(vNormalVector),normalize(vLightVector)),0.0f);

	// Sample the shadow map 16 times, 4 texture() calls * 4 samples each call
	float visibility = 1.0;
	float bias = 0.005*tan(acos(cosTheta));
	bias = clamp(bias, 0.0f,0.01f);
	int sampleNum = 4;
	for (int i=0;i<sampleNum;i++)
		visibility -= (1.0f/sampleNum)*(1.0-texture(depthBuffer,vec3(vShadowCoord.xy + poissonDisk[i]/700.0,(vShadowCoord.z-bias)/vShadowCoord.w)));

	color = vec4(matDiffuseColor*ambientLightColor*ambientLightPower + //ambient light
				 matDiffuseColor*sunLightColor*sunLightPower*visibility*cosTheta + //sun light (diffuse)
				 matSpecularColor*sunLightColor*sunLightPower*visibility*pow(cosAlpha,10)*cosTheta,1.0f); //sun light (specular)
}
