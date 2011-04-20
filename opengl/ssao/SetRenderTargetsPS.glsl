
varying vec3 normal;
varying vec4 color;
varying vec2 depthPos;
varying vec4 viewSpacePos;

void main()
{
  vec3 n = normalize(normal);
  float depthVal = depthPos.x / depthPos.y;

  gl_FragData[0] = color;
  gl_FragData[1] = vec4(n, 1.0);
  gl_FragData[2] = vec4(viewSpacePos.xyz, 1.0);
}
