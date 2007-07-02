
uniform vec3 	lightPosition;
varying float 	lightIntensity;

varying vec3 	position;

attribute vec3 	texCoord;

void main(void) 
{
	vec4 pos = gl_ModelViewMatrix * gl_Vertex;
	Position = vec3(gl_Vertex) * Scale;
	vec3 tnorm = normalize(gl_NormalMatrix * gl_Normal);
       float dotval = max(dot(normalize(LightPosition - vec3(pos)),tnorm), 0.0);
	lightIntensity = dotval * 1.5;

  	texCoord = vec3( gl_MultiTexCoord0 );

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
