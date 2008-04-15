
//uniform sampler2D normalMap;


//varying	vec3 lightDir;
//varying	vec3 eyeDir;

//varying vec3 t;
varying vec3 b;
//varying vec3 n;

void main()
{   
	/*vec3  litColor = vec3( 0.0, 0.0, 0.0 );
	
	float spec;	
	float diff;
		
	vec3 bump = ( texture2D( normalMap, gl_TexCoord[0].xy ).rgb -  0.5 ) * 2.0 ;
	
	vec3 pNormal = normalize( bump );		

	vec3 reflectDir = reflect( pNormal, lightDir );	
	
	spec = max( dot( eyeDir, reflectDir ), 0.0 );	
	
	litColor = gl_FrontMaterial.specular.xyz * gl_LightSource[0].specular.xyz * pow( spec,  gl_FrontMaterial.shininess );
			
	diff = max( dot( pNormal, lightDir ), 0.3 );
	
	litColor = ( gl_FrontMaterial.diffuse.xyz * gl_LightSource[0].diffuse.xyz * diff ) + litColor;
	
	litColor = min( litColor, vec3( 1.0 ) );	*/
	
	gl_FragColor = vec4( b, 1.0 );
}
