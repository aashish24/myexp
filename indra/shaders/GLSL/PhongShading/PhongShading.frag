
uniform sampler2D NormalMap;

varying	vec3      lightDir;
varying	vec3      eyeDir;

varying vec3        normal;
varying vec3        lightPos;

void main()
{   
	vec3  litColor  = vec3( 0.0, 0.0, 0.0 );
	float spec      = 0.0;	
	float diff      = 0.0;
	
	/*	
	vec3 bump       = ( texture2D( NormalMap, gl_TexCoord[0].xy ).rgb -  0.5 ) * 2.0 ;
	vec3 pNormal    = normalize( vec3( bump[0], bump[1], bump[2] ) );		
	vec3 reflectDir = normalize( reflect( -lightDir, pNormal ) );	
	diff            = max( dot( lightDir, pNormal ), 0.0 );
	*/
	
	vec3 reflectDir = normalize( reflect( -lightDir, normal ) );
	
	spec            = max( dot( -eyeDir, reflectDir ), 0.0 );	
	litColor        = gl_FrontMaterial.specular.xyz * gl_LightSource[0].specular.xyz * pow( spec, 80.0 );
		
	diff            = max( dot( lightDir, normal ), 0.0 );
	litColor        = ( gl_FrontMaterial.diffuse.xyz * gl_LightSource[0].diffuse.xyz * diff ) + litColor;
	
	litColor        = min( litColor, vec3( 1.0 ) );		
	
	gl_FragColor    = vec4( litColor, 1.0 );
}

