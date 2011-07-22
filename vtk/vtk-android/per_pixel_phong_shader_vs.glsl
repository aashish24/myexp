//varying vec4 vPosition;
//varying vec3 vNormal;
//varying vec3 vLightDir;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

//attribute vec4 normals;
attribute vec3 positions;

void main(void)
{
//  vec4 lightPosition = vec4(0, 100, 10, 1);
  vec4 position = vec4(positions, 1.0);
  gl_Position = viewMatrix * modelMatrix * position;
//  vPosition = gl_ModelViewMatrix * positions;

//  vLightDir = normalize(vec3(lightPosition - vPosition));
//  vNormal = vec3(normals);
}

