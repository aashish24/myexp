
attribute vec4   tangent;
attribute vec4   binormal;

varying vec3    lightDir;
varying vec3    eyeDir;

/*
vec3            t;
vec3            b;
vec3            n;
*/

varying vec3     normal;
varying vec3     lightPos;

void main()
{ 
  gl_Position     = ftransform();	
	
	gl_TexCoord[0]  = gl_MultiTexCoord0;	
	
	normal          = normalize( gl_NormalMatrix * gl_Normal );
	
	/*
	t               = normalize( gl_NormalMatrix * vec3( tangent[0], tangent[1], tangent[2] ) ) ;
	n               = normalize( gl_NormalMatrix * gl_Normal );
	b               = normalize( gl_NormalMatrix * vec3( binormal[1], binormal[2], binormal[3] ) ) ;		
  */
  
  eyeDir          = normalize(  vec3( gl_ModelViewMatrix * gl_Vertex ) );
  
  /*
  lightPos        = normalize(  vec3( 0.0, 0.0, 10.0 ) );
  */
  
  // Need to multiply light position with gl_NormalMatrix as OpenGL and OSG live 
  // in different coordintate system. 
  lightPos        = normalize( gl_LightSource[0].position.xyz * gl_NormalMatrix );       
  lightDir        = normalize( lightPos - eyeDir );
  
  /*
  vec3 v        = vec3( 0.0, 0.0, 0.0 );	 
  
	v.x            = dot( ( lightPos ), t );
	v.y             = dot( ( lightPos ), b );
	v.z             = dot( ( lightPos ), n );	
	
	lightDir        = normalize( v );
	
	v.x             = dot( eyeDir, t );
	v.y             = dot( eyeDir, b );
	v.z             = dot( eyeDir, n );	
	
	eyeDir          = normalize( v );	
	*/
}


