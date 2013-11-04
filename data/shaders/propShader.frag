#version 420 core

uniform sampler2D sampler;
uniform sampler2DShadow depthBuffer;

in vec2 vTexCoord;
in vec4 vShadowCoord;
in vec3 vNormal;
in vec3 lightDirection;

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

	// Light emission properties
	vec3 lightColor = vec3(1,1,1);
	float lightPower = 0.2f;

	// Material properties
	vec3 MaterialDiffuseColor = texture2D(sampler,vTexCoord).rgb;
	vec3 MaterialAmbientColor = vec3(0.8,0.8,0.8) * MaterialDiffuseColor;

	float cosTheta = max(dot(normalize(vNormal), normalize(lightDirection)), 0.0);

	float visibility=1.0;
	float bias = 0.005*tan(acos(cosTheta));
	bias = clamp(bias, 0.0f,0.01f);

	// Sample the shadow map 16 times, 4 texture() calls * 4 samples each call
	int sampleNum = 4;
	for (int i=0;i<sampleNum;i++)
		visibility -= (1.0f/sampleNum)*(1.0-texture(depthBuffer,vec3(vShadowCoord.xy + poissonDisk[i]/700.0,(vShadowCoord.z-bias)/vShadowCoord.w)));
	vec3 materialColor = texture(sampler,vTexCoord).xyz;
	color = vec4(MaterialAmbientColor +
				 lightColor*cosTheta*visibility*lightPower,1.0f);
}
