
varying vec2 texCoords;

uniform vec3 light1Pos;
uniform vec4 light1AmbientColor;
uniform vec4 light1DiffuseColor;
uniform vec4 light1SpecularColor;

uniform vec3 light2Pos;
uniform vec4 light2AmbientColor;
uniform vec4 light2DiffuseColor;
uniform vec4 light2SpecularColor;

uniform sampler2D colors;
uniform sampler2D aos;
uniform sampler2D depths;
uniform sampler2D normals;

void main()
{
  vec3 color = texture2D(colors, texCoords);
  float ao = texture2D(aos, texCoords).x;

  // Ambient light.
  vec3 ambient = color * (light1AmbientColor + light2AmbientColor);
  ambient      = ambient.rgb * ao;

  // Diffuse light.
  float diffuseComponent1 = dot( normalize( texture2D(normals, texCoords).xyz), normalize(light1Pos) );
  diffuseComponent1       = max(diffuseComponent1, 0.0);

  float diffuseComponent2 = dot( normalize( texture2D(normals, texCoords).xyz), normalize(light2Pos) );
  diffuseComponent2       = max(diffuseComponent2, 0.0);

  vec3 diffuse  = (color * light1DiffuseColor) * diffuseComponent1 + (color * light2DiffuseColor) * diffuseComponent2;
  diffuse       = clamp(diffuse, 0.0, 1.0);

  gl_FragColor = vec4( clamp(ambient + diffuse, 0.0, 1.0), 1.0 );
}
