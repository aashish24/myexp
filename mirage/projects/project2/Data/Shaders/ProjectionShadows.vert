
uniform vec4 	uLightPos;

uniform vec3	n;
uniform float	d;


varying vec4	vPos;


void main()
{
	vec3 	v;
	vec3    l;
	mat4 	projectionMat;
		
	l 					= ( uLightPos.xyz );							
	
	v 					= vec3( gl_Vertex );	
					
	projectionMat 		= mat4( ( dot( n, l ) + d - l.x * n.x ), -l.y * n.x,                      -l.z * n.x,                       -n.x, 
						                 -l.x * n.y,                     ( dot( n, l ) + d - l.y * n.y ), -l.z * n.y,                       -n.y, 
						                 -l.x * n.z,                     -l.y *n.z,                      ( dot( n, l ) + d - l.z * n.z ),   -n.z, 
						                 -l.x*d,                         -l.y*d,                          -l.z*d,                           dot( n, l ) );				
	
	//projectionMat 	= mat4( l.y, -l.x, 0, 0, 0, 0, 0, 0, 0, -l.z, l.y, 0, 0, -1, 0, l.y );	
	//gl_Position	 	= gl_ModelViewProjectionMatrix * projectionMat * gl_Vertex;
	
	vPos 				=  gl_ModelViewProjectionMatrix * projectionMat * vec4( v, 1.0 );
	
	gl_Position 		= vPos;
} 
