
varying vec3 v; 
varying vec3 n;

void main()
{
	gl_Position = ftransform();
	v 			    = vec3( gl_ModelViewMatrix * gl_Vertex );
	n 			    = vec3( gl_NormalMatrix * gl_Normal );	
} 
