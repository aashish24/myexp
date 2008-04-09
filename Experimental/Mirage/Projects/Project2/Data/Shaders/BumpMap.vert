

uniform   vec3   uLightPos;
   
attribute vec3   tangent;
attribute vec3   binormal;

varying   vec3   lightDir;
varying   vec3   eyeDir;

varying vec3     t;

varying vec3     b;
varying vec3     n;

void main()
{
	gl_Position     = ftransform();	
	gl_TexCoord[0]  = gl_MultiTexCoord0;	
	
	eyeDir          = vec3( gl_ModelViewMatrix * gl_Vertex );
	
	t               = normalize( gl_NormalMatrix * tangent );
	n               = normalize( gl_NormalMatrix * gl_Normal );
	b               = normalize( gl_NormalMatrix * binormal );		

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
}


