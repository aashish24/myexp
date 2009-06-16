varying vec3 n;
varying vec3 t;
varying vec3 b;

varying vec3 iv;
varying vec3 il;

void main()
{	gl_Position = ftransform();	

	gl_TexCoord[0]  = gl_MultiTexCoord0;	
	gl_TexCoord[1]  = gl_MultiTexCoord1;	
	gl_TexCoord[2]  = gl_MultiTexCoord2;	
	
	n = normalize( gl_NormalMatrix * gl_Normal );
	t = normalize( gl_NormalMatrix * gl_TexCoord[1].xyz );
	b = normalize( gl_NormalMatrix * gl_TexCoord[2].xyz );
		
	iv = vec3( gl_ModelViewMatrix * gl_Vertex );
	il = vec3( 0.0, 100.0, 1000.0 );
}