
uniform sampler2D uSphereMap;

void main (void)
{
  vec4 envColor;
  
  envColor      = texture2D( uSphereMap, vec2( gl_TexCoord[0].xy ) ).rgba;
  gl_FragColor  = envColor;
}
