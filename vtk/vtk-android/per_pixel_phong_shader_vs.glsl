//varying vec4 vPosition;
//varying vec3 vNormal;
//varying vec3 vLightDir;

uniform mat

//attribute vec4 normals;
attribute vec4 positions;

void main(void)
{
//  vec4 lightPosition = vec4(0, 100, 10, 1);
  gl_Position = gl_ModelViewProjectionMatrix * positions;
//  vPosition = gl_ModelViewMatrix * positions;

//  vLightDir = normalize(vec3(lightPosition - vPosition));
//  vNormal = vec3(normals);
}

