varying vec3 n;
varying vec3 v;

void main()
{
	gl_Position	= ( gl_ModelViewProjectionMatrix * gl_Vertex );	
	v			= vec3( gl_ModelViewMatrix * gl_Vertex );
	n		   	= normalize( gl_NormalMatrix * gl_Normal );		
} 

