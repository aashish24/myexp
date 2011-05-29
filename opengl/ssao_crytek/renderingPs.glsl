
varying vec2 texCoords;

uniform vec3 lightPos;
uniform vec4 lightColor;

uniform sampler2D colors;
uniform sampler2D aos;
uniform sampler2D depths;
uniform sampler2D normals;

void main()
{
  vec3 color = texture2D(colors, texCoords) * 0.5;
  float ao = texture2D(aos, texCoords).x;

  // Ambient light.
  vec3 ambient = color + lightColor * 0.5;
  ambient      = ambient.rgb * ao;

  // Diffuse light.
  float diffuseComponent = dot( normalize( texture2D(normals, texCoords).xyz), normalize(lightPos) );
  diffuseComponent = max(0.0, diffuseComponent);

  vec3 diffuse = color;
  diffuse = diffuse * diffuseComponent;

  gl_FragColor = vec4( clamp(ambient + diffuse, 0.0, 1.0), 1.0);
}
