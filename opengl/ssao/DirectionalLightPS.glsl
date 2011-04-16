
varying vec2 texCoords;

uniform sampler2D colors;
uniform sampler2D aos;

uniform vec3 lightPos;
uniform vec4 lightColor;

void main()
{
  gl_FragColor = vec4(texture2D(aos, texCoords).xyz, 1.0);
}
