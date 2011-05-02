
varying vec2 texCoords;

uniform sampler2D colors;
uniform sampler2D aos;

uniform vec3 lightPos;
uniform vec4 lightColor;

void main()
{
  float ao = texture2D(aos, texCoords).x;
  vec4 ambient = vec4(1.0, 1.0, 1.0, 1.0);
  ambient.rgb = ambient.rgb * ao * 1.1;
  gl_FragColor = ambient;
}
