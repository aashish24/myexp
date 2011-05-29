
varying vec2 texCoords;

uniform vec3 lightPos;
uniform vec4 lightColor;

uniform sampler2D colors;
uniform sampler2D aos;
uniform sampler2D depths;
uniform sampler2D normals;

void main()
{
  vec3 diffuseColor = vec3(0.0, 0.5, 0.5);

  float ao = texture2D(aos, texCoords).x;

  // Ambient light.
  vec4 ambient = vec4(1.0, 1.0, 1.0, 1.0);
  ambient.rgb = ambient.rgb * ao;

  // Diffuse light.
  float diffuseComponent = dot( normalize( texture2D(normals, texCoords).xyz), normalize(lightPos) );
  diffuseComponent = max(0.0, diffuseComponent);
  vec4 diffuse = vec4(diffuseColor.rgb * diffuseComponent, 1.0);

  gl_FragColor = ambient + diffuse;
}
