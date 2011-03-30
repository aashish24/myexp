varying vec4 vPosition;
varying vec3 vNormal;
varying vec3 vLightDir;

attribute vec4 normals;

void main(void)
{
  vec4 lightPosition = vec4(0, 100, 10, 1);
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  vPosition = gl_ModelViewMatrix * gl_Vertex;

  vLightDir = normalize(vec3(lightPosition - vPosition));
  vNormal = vec3(normals);
}

