
uniform samplerCube 	uCubeMap;
uniform sampler2D 		uNormalMap;

varying vec3        	eyeDirES;

varying float       	lightIntensity;

varying	vec3			    t;
varying vec3			    b;
varying vec3			    n;

void main (void)
{	
  vec3 bump      		= ( texture2D( uNormalMap, gl_TexCoord[0].xy ).rgb * 2.0 ) - 1.0;	
	
	vec3 pNormal  		= normalize( bump );
	
	pNormal.z				  = pNormal.z  * 2.0;
	mat3 mat			    = mat3( t[0], t[1], t[2], b[0], b[1], b[2], n[0], n[1], n[2] );	
	
	
	vec3 newNormal		= pNormal;	
	
	newNormal			    = normalize( vec3( mat * pNormal ) );
		
	vec3 reflectDirES = reflect( eyeDirES, newNormal );
  vec3 envColor  		= vec3( textureCube( uCubeMap, reflectDirES ) );
  
  vec3 baseColor    = gl_FrontLightProduct[0].diffuse.xyz;
  
  vec3 color        = mix( envColor, baseColor, 0.0 );
  
  gl_FragColor		  = vec4( color, 1.0 );    
}





   
