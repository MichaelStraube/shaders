/*
 *  3d matrix rain by laserdog
 *
 *  https://www.shadertoy.com/view/MsVBDG
 */

#version 330 core
in vec2 TexCoord;

uniform vec3 iResolution;
uniform float iTime;
uniform sampler2D iChannel0;

float random (in float x) {
	return fract(sin(x)*1e4);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy / iResolution.xy - vec2(.5);
	vec2 lookup = vec2(uv.x / uv.y, .5 / uv.y) * .55;
	float rand = random(floor(lookup.x * 16.)) + .1;
	float ySign = sign(uv.y);

	lookup.y += (iTime + 10.) * rand * ySign + rand * 7.85;
	float r = texture(iChannel0, lookup).r
	// if i don't do this, i get weird artifacts. not sure why
	* step(.1 / 16., abs(lookup.x - round(lookup.x * 16.) / 16.));

	const float charsPerSegment = 20.;
	float sectionSize = charsPerSegment / 16.;
	float diff = ySign == -1. ? mod(lookup.y, sectionSize) : sectionSize - mod(lookup.y, sectionSize);
	r *= pow(diff / sectionSize, 2.75) * 1.2 * pow(rand, 2.);

	fragColor.rgb = vec3(0., 1., 0.2) * r * abs(uv.y) * 35.;
}

void main()
{
	mainImage(gl_FragColor, gl_FragCoord.xy);
}
