
// 2D texture sampler. 
uniform sampler2D normalMap;

// Interpolated light and eye directions. 
varying	vec3 lightDir;
varying	vec3 eyeDir;

// Interpolated tangent, binormal and normal vectors. 
varying vec3 t;
varying vec3 b;
varying vec3 n;

void main()
{   
	// Final color of the fragment initialized to 0.0. 
	vec3  litColor = vec3( 0.0, 0.0, 0.0 );
	
	// Convert perturbed normal information stored as RGB to range [-1.0, 1.0]. 	
	vec3 bump = ( texture2D( normalMap, gl_TexCoord[0].xy ).rgb -  0.5 ) * 2.0 ;
	
	// Normalize perturbed normal.  
	vec3 pNormal = normalize( bump );		

	// Calculate reflection direction. 
	vec3 reflectDir = reflect( pNormal, lightDir );	
	
	// Calculate specular parameter. 
	float spec = max( dot( eyeDir, reflectDir ), 0.0 );	
	
	// Calculate diffuse parameter.	
	float diff = max( dot( pNormal, lightDir ), 0.3 );
	
	// Calculate fragment color using specular and diffuse light components.  
	litColor = gl_FrontMaterial.specular.xyz * gl_LightSource[0].specular.xyz * pow( spec,  gl_FrontMaterial.shininess ) + 
			   gl_FrontMaterial.diffuse.xyz * gl_LightSource[0].diffuse.xyz * diff; 	
	
	// @Test. 
	//litColor = gl_FrontMaterial.specular.xyz * gl_LightSource[0].specular.xyz * pow( spec,  gl_FrontMaterial.shininess );			   
				
	// Chop off values greater then 1.0.
	litColor = min( litColor, vec3( 1.0 ) );
	
	// Set fragment color.
	gl_FragColor = vec4( litColor, 1.0 );
	
	// @Test
	//gl_FragColor = vec4( b, 1.0 );
}
