
// 2D texture sampler. 
uniform sampler2D normalMap;
uniform sampler2D decalMap;

// Check whether or not we have the decal map. 
uniform bool useDecalMap;

// Interpolated light and eye directions. 
varying	vec3 lightDir;
varying	vec3 eyeDir;

// @Note: For testing. 
varying vec3 t;
varying vec3 b;
varying vec3 n;

varying vec3 vForLight;

void main()
{	
	// Final color of the fragment initialized to 0.0. 
	vec3  litColor = vec3( 0.0, 0.0, 0.0 );
	
	// Convert perturbed normal information stored as RGB to range [-1.0, 1.0]. 	
    vec3 bump = ( texture2D( normalMap, gl_TexCoord[0].xy ).rgb -  0.5 ) * 2.0 ;    

	// 
	bump[0] = bump[0] * 4.0;
	bump[1] = bump[1] * 4.0;
	
	// Read the color value from diffuse map. 
	vec3 color = ( texture2D( decalMap, gl_TexCoord[0].xy ).rgb );
	
	//@Test
	//vec3 bump = ( texture2D( normalMap, gl_TexCoord[0].xy ).rgb ); 
		
	// Normalize perturbed normal.  
	vec3 pNormal = normalize( bump );		

	// 
	lightDir = normalize( lightDir );
	eyeDir = normalize( eyeDir );

	// Calculate reflection direction. 
	vec3 reflectDir = -reflect( pNormal, lightDir );	
	
	// Calculate specular parameter. 
	float spec = max( dot( eyeDir, reflectDir ), 0.0 );	
	
	// Calculate diffuse parameter.	
	float diff = max( dot( pNormal, lightDir ), -1.0 );
	
	// Calculate diffuse based off actual normals. 
	n = normalize( n );
	vec3 l = normalize( gl_LightSource[0].position.xyz - vForLight );
	float diff2 = max( dot( n, l ), -1.0 );
	
	//
	vec3 diffuseColor = gl_FrontMaterial.diffuse.xyz * gl_LightSource[0].diffuse.xyz * diff;
	
	// Part of an experimentation. 
	vec3 diffuseColor2 = gl_FrontMaterial.diffuse.xyz * gl_LightSource[0].diffuse.xyz * diff2;
	
	vec3 diffuseColorMix;
	
	// Part of an experimentation. 
	//diffuseColorMix = min( mix(  diffuseColor, diffuseColor2, 0.5 ), 1.0 );
	
	// 
	diffuseColorMix = min( diffuseColor, 1.0 );	
	
	if( useDecalMap ) 
	{
		diffuseColorMix = min( mix(  diffuseColorMix, color, 0.5 ), 1.0 ); 
	}
	
	// Calculate fragment color using specular and diffuse light components.  	
	//litColor = gl_FrontMaterial.specular.xyz * gl_LightSource[0].specular.xyz * pow( spec,  gl_FrontMaterial.shininess ) + 
	//		   gl_FrontMaterial.diffuse.xyz * gl_LightSource[0].diffuse.xyz * diff + gl_FrontMaterial.ambient.xyz * gl_LightSource[0].ambient.xyz  ; 	
	
	litColor = gl_FrontMaterial.specular.xyz * gl_LightSource[0].specular.xyz * pow( spec,  gl_FrontMaterial.shininess ) + 
			   diffuseColorMix + gl_FrontMaterial.ambient.xyz * gl_LightSource[0].ambient.xyz  ; 	
	
	// @Test. 
	//litColor = gl_FrontMaterial.specular.xyz * gl_LightSource[0].specular.xyz * pow( spec,  gl_FrontMaterial.shininess );			   
				
	// Chop off values greater then 1.0.
	litColor = min( litColor, vec3( 1.0 ) );
	
	// @Note: Now we are mixing only diffuse components. 
	//litColor = min( mix( litColor, color, 0.2 ), 1.0 );
	
	// Set fragment color.
	gl_FragColor = vec4( litColor, 1.0 );
	
	// @Test
	//gl_FragColor = vec4( b, 1.0 );
}

