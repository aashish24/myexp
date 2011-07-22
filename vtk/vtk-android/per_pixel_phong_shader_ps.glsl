varying vec4 vPosition;
varying vec3 vNormal;
varying vec3 vLightDir;

void main(void)
{
  float diff = max(dot(vNormal.xyz, vLightDir), 0.0);
  gl_FragColor = vec4(1, 1.0, 1.0, 1.0) * diff;
//  gl_FragColor = vec4(vNormal.xyz, 1.0);
//  gl_FragColor = vec4(vLightDir, 1.0);
//  gl_FragColor = vec4(vec3(diff), 1.0);
}

