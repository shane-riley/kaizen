#version 120

attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec4 vNormal;
varying vec4 color;

uniform mat4 ctm1;
uniform mat4 ctm2;
uniform vec4 lightPosition;
uniform vec4 eye;
float shininess = 10;
vec4 ambient = vec4(.3, .3, .3, 1);
vec4 diffuse = vec4(1, 1, 1, 1);
vec4 specular = vec4(1, 1, 1, 1);
float attConst = 1;
float attLinear = .01;
float attQuad = .01;
vec4 a, d, s;



void main()
{
	vec4 n = normalize(ctm1 * ctm2 * vNormal);
	vec4 lTemp = (lightPosition) - (ctm1 * ctm2 * vPosition);
	vec4 L = normalize(lTemp);
	vec4 d = max(dot(L, n), 0) * diffuse;
	vec4 V = normalize(eye - (ctm1 * ctm2 * vPosition));
	vec4 H = normalize(L + V);
	vec4 s = pow(max(dot(n, H), 0.0), shininess) * specular;
	float distance = length(lTemp);
	float attenuation = 2/(attConst + (attLinear * distance) + (attQuad * distance * distance));
	color = (vColor * (ambient + (attenuation * (d+s))));
	gl_Position = ctm1 * ctm2 * vPosition;
}
