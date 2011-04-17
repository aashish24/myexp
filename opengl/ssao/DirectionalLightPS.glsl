
varying vec2 texCoords;

uniform sampler2D colors;
uniform sampler2D aos;

uniform vec3 lightPos;
uniform vec4 lightColor;

void main()
{
//  vec4 ambient = clamp(vec4(0.9, 0.9, 0.9, 1.0) + vec4(texture2D(colors, texCoords).xyz,1.0), 0.0, 1.0);
  float ao = texture2D(aos, texCoords).x;
//  ambient.rgb *= ao;
//  gl_FragColor = ambient;
  vec4 ambient = vec4(0.9, .9, .9, 1.0);
  ambient.rgb = ambient.rgb * ao;
  gl_FragColor = ambient;
}
