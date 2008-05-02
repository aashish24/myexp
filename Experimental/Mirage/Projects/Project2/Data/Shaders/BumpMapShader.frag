
// 2D texture sampler. 
uniform sampler2D normalMap;
uniform sampler2D decalMap;

// Check whether or not we have the decal map. 
uniform bool useDecalMap;

// Interpolated light and eye directions. 
vec3 lightDir;
vec3 eyeDir;

// @Note: For testing. 
varying vec3 t;
varying vec3 b;
varying vec3 n;

varying vec3 iv; 
varying vec3 il;

//varying vec3 vForLight;

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
	
	// Normalize perturbed normal.  
	vec3 pNormal = normalize( bump );		

	// Normalize. 
	lightDir = normalize( il - iv );	
	
	t = normalize( t );
	b = normalize( b );
	n = normalize( n );	
	
	// In tangent space. 
	vec3 v;
	v.x = dot( t, ( lightDir ) );
	v.y = dot( b, ( lightDir ) );
	v.z = dot( n, ( lightDir ) );		
	lightDir = normalize( v );	
		
	eyeDir = normalize( iv );	
	v.x = dot( t, ( eyeDir ) );
	v.y = dot( b, ( eyeDir ) );
	v.z = dot( n, ( eyeDir ) );		
	
	eyeDir = -normalize( v );		
	
	// Calculate reflection direction. 
	vec3 reflectDir = -reflect( pNormal, lightDir );	
	
	// Calculate specular parameter. 
	float spec = max( dot( eyeDir, reflectDir ), 0.0 );	
	
	// Calculate diffuse parameter.	
	// @Note: We are setting the range of [-1.0, 1.0] 
	// so that we could negate of the color component as we get from 
	// the color map. 
	float diff;
	
	if( useDecalMap )
	{
		diff = max( dot( pNormal, lightDir ), -1.0 );	
	}
	else
	{
		diff = max( dot( pNormal, lightDir ), 0.0 );	
	}	
	
	
	// Calculate diffuse component. 
	vec3 diffuseColor = gl_FrontMaterial.diffuse.xyz * gl_LightSource[0].diffuse.xyz * diff;
	
	// Part of an experimentation. 
	//vec3 diffuseColor2 = gl_FrontMaterial.diffuse.xyz * gl_LightSource[0].diffuse.xyz * diff2;
	
	vec3 diffuseColorMix;
	
	// Part of an experimentation. 
	//diffuseColorMix = min( mix(  diffuseColor, diffuseColor2, 0.5 ), 1.0 );
	
	// 
	diffuseColorMix = min( diffuseColor, 1.0 );	
	
	if( useDecalMap ) 
	{
		diffuseColorMix = min( mix(  diffuseColorMix, color, 0.3 ), 1.0 ); 
	}
	
	// Calculate fragment color using specular and diffuse light components.  	
	//litColor = gl_FrontMaterial.specular.xyz * gl_LightSource[0].specular.xyz * pow( spec,  gl_FrontMaterial.shininess ) + 
	//		   gl_FrontMaterial.diffuse.xyz * gl_LightSource[0].diffuse.xyz * diff + gl_FrontMaterial.ambient.xyz * gl_LightSource[0].ambient.xyz  ; 	
	
	litColor = gl_FrontMaterial.specular.xyz * gl_LightSource[0].specular.xyz * pow( spec,  gl_FrontMaterial.shininess ) + 
			   diffuseColorMix + gl_FrontMaterial.ambient.xyz * gl_LightSource[0].ambient.xyz  ; 	
			
	// Chop off values greater then 1.0.
	litColor = min( litColor, vec3( 1.0 ) );
	
	
	// Set fragment color.
	gl_FragColor = vec4( t, 1.0 );	
}

