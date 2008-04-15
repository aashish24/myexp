
attribute vec3 binormal;
//attribute vec3 tangent;

//varying vec3 lightDir;
//varying vec3 eyeDir;

//varying vec3 t;
varying vec3 b;
//varying vec3 n;

void main()
{
	gl_Position = ftransform();	
	//t = tangent;
	b = binormal;
	
	/*gl_TexCoord[0]  = gl_MultiTexCoord0;	

	eyeDir = vec3( gl_ModelViewMatrix * gl_Vertex );


	//t = normalize( gl_NormalMatrix * tangent );
	n = normalize( gl_NormalMatrix * gl_Normal );
	//b = normalize( gl_NormalMatrix * binormal );			
	
	vec3 lightPos =  vec4( gl_LightSource[0].position.xyz, 1.0 ).xyz;
	
	vec3 v;	
	
	v.x = dot( t, ( gl_LightSource[0].position.xyz ) );
	v.y = dot( b, ( gl_LightSource[0].position.xyz ) );
	v.z = dot( n, ( gl_LightSource[0].position.xyz ) );	

	lightDir = normalize( v );

	v.x = dot( eyeDir, t );
	v.y = dot( eyeDir, b );
	v.z = dot( eyeDir, n );	

	eyeDir = normalize( v );*/	
}


