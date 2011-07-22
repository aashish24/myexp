varying vec4 vPosition;
varying vec3 vNormal;
varying vec3 vLightDir;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

attribute vec3 normals;
attribute vec3 positions;

void main(void)
{
  vec4 lightPosition = vec4(0.0, 10.0, 100.0, 1.0);

  vec4 position = vec4(positions, 1.0);
  vec4 normal   = vec4(normals, 0.0);

  gl_Position = viewMatrix * modelMatrix * position;

  vPosition = viewMatrix * modelMatrix * position;
  vLightDir = normalize(vec3(lightPosition - vPosition));
  vNormal   = vec3(modelMatrix * normal);
  vNormal   = normalize(vec3(normal));

}

