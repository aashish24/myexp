
uniform vec3 	uLightPos;

varying  vec3  	eyeDirES;
varying float 	lightIntensity;

attribute vec3 	tangent;

varying vec3	  t;
varying vec3	  b;
varying vec3	  n;

void main(void) 
{
	vec3 normal		  = normalize( gl_NormalMatrix * gl_Normal );
  vec4 pos        = gl_ModelViewMatrix * gl_Vertex;
    
  eyeDirES        = pos.xyz;
    
  lightIntensity 	= max( dot( normalize( uLightPos - eyeDirES ), normal ), 0.0 );    
    
  gl_TexCoord[0] 	= gl_MultiTexCoord0;
	
	t          		  = normalize( gl_NormalMatrix * tangent );
	n          		  = normalize( gl_NormalMatrix * gl_Normal );
	b         		  = normalize( cross( n, t ) );	
	
	gl_Position    	= ftransform();
 }
