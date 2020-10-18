/*
 *  based on https://www.shadertoy.com/view/WsfGDM
 */

#version 330 core
uniform vec2 iResolution;
uniform float iTime;

vec2 hash22(vec2 p)
{
	vec3 p3 = fract(vec3(p.xyx) * vec3(.1031, .1030, .0973));
	p3 += dot(p3, p3.yzx+19.19);
	return fract((p3.xx+p3.yz)*p3.zy);
}

float noise(in vec2 p)
{
	vec2 n = floor(p);
	vec2 f = fract(p);

	float md = 1.0;

	// Scale a bit to move from cell edges
	vec2 o = hash22(n)*0.96 + 0.02;

	vec2 r = o - f;
	float d = dot(r, r);

	md = min(d, md);

	return md;
}

vec3 starfield(vec2 samplePosition, float threshold)
{
	float starValue = noise(samplePosition);

	float power = max(1.0 - (starValue / threshold), 0.0);
	power = power * power * power;

	return vec3(power);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	float maxResolution = max(iResolution.x, iResolution.y);

        #define STAR_LAYER_COUNT 3

	vec3 finalColor = vec3(0);
	vec2 sCoord = (fragCoord.xy / maxResolution)*5.0;
	vec2 pos = vec2(iTime * 0.4, fragCoord.y);

	// Add starfields
	for (int i = 1; i <= STAR_LAYER_COUNT; i++) {
		float fi = float(i);
		float inv = sqrt(1.0/fi);
		finalColor += starfield((sCoord + vec2(fi*100.0, -fi*50.0)) * (1.0 + fi * 0.2) + pos, 0.0002)*inv;
	}

	fragColor = vec4(finalColor, 1.0);
}

void main()
{
	mainImage(gl_FragColor, gl_FragCoord.xy);
}
