
// Per vertex normal. 
varying vec3 n;

// Vertex location. 
varying vec3 v;

// Half vector. 
varying vec3 h;

void main()
{
	gl_Position	 = ( gl_ModelViewProjectionMatrix * gl_Vertex );	
	
	v = vec3( gl_ModelViewMatrix * gl_Vertex );
	n	= normalize( gl_NormalMatrix * gl_Normal );		
	
	// OpenGL can calculate half vector for us. 
	h	= normalize( gl_LightSource[0].halfVector.xyz );
} 
