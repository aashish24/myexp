

uniform   vec3   uLightPos;
   
attribute vec4   tangent;
attribute vec4   binormal;

varying   vec3   lightDir;
varying   vec3   eyeDir;

varying vec3     t;

varying vec3     b;
varying vec3     n;

varying vec3     bnormal;

void main()
{  

  bnormal = vec3( binormal[1], binormal[2], binormal[3] );
    
	gl_Position     = ftransform();	
	gl_TexCoord[0]  = gl_MultiTexCoord0;	
	
	eyeDir          = vec3( gl_ModelViewMatrix * gl_Vertex );
	
	t               = normalize( gl_NormalMatrix * vec3( tangent[1], tangent[2], tangent[3] ) );
	n               = normalize( gl_NormalMatrix * gl_Normal );
	b               = normalize( gl_NormalMatrix * vec3( binormal[1], binormal[2], binormal[3] ) );		

  vec3 lightPos   =  vec4( uLightPos, 1.0 ).xyz;

	vec3 v;	
	v.x             = dot( t, ( lightPos ) );
	v.y             = dot( b, ( lightPos ) );
	v.z             = dot( n, ( lightPos ) );	
	
	lightDir        = normalize( v );
	
	v.x             = dot( eyeDir, t );
	v.y             = dot( eyeDir, b );
	v.z             = dot( eyeDir, n );	
	
	eyeDir          = normalize( v );	
		
		lightDir        = vec3( 0.0, 0.0, 10.0 );
}


