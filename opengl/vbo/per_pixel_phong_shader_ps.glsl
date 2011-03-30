varying vec4 position;
varying vec3 vNormal;
varying vec3 vLightDir;

void main(void)
{
  float diff = max(dot(vNormal.xyz, vLightDir), 0.0);
  gl_FragColor = vec4(0.2, 0.2, 0.7, 1.0) * diff;
}

