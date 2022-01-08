#version 120

varying vec4 color;
varying vec2 texCoord;

uniform sampler2D texture;

void main()
{

	if (texCoord.x == -1.0) {
		gl_FragColor = vec4(0,1,0,1);
	} else if (texCoord.x == -2.0) {
		gl_FragColor = vec4(0,0,1,1);
	} else {
		gl_FragColor = texture2D(texture, texCoord);
	}
}
