#version 110

uniform sampler2D texture1;

uniform vec2 time;
uniform float amount;

// This is the built-in random number generator from the strf-library
float random(float);

void main() {
	// Calculate texture coordinates
	vec2 coords = gl_TexCoord[0].st + 0.02 * sin(amount * vec2(gl_TexCoord[0].t, gl_TexCoord[0].s));
	// Get texture color
	vec4 tex = texture2D(texture1, coords);
	// Calculate color
	vec4 color = gl_Color * vec4(0.96, 0.96, 0.995, 1.0);
	// Calculate random noise
	vec4 rand = vec4(vec3(random(sin(time.s) + cos(time.t) + gl_FragCoord.x * 0.1 + gl_FragCoord.y * 10.0) * 0.3 - 0.2), 0.0);
	// Set the fragment color
	gl_FragColor = tex * color + rand;
}
