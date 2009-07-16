// 2D texture sampler. 
uniform sampler2D normalMap;
uniform sampler2D heightMap; 
uniform sampler2D decalMap; 

// Interpolated light and eye directions. 
vec3 lightDir;
vec3 eyeDir;

varying vec3 t;
varying vec3 b;
varying vec3 n;

varying vec3 iv; 
varying vec3 il;


void main()
{	
	// Final color of the fragment initialized to 0.0. 
	vec3  litColor = vec3( 0.0, 0.0, 0.0 );
	
	// Normalize. 
	lightDir = normalize( il - iv );	
	
	vec3 nt = normalize( t );
	vec3 nb = normalize( b );
	vec3 nn = normalize( n );	
	
	// In tangent space. 
	vec3 v;
	v.x = dot( nt, ( lightDir ) );
	v.y = dot( nb, ( lightDir ) );
	v.z = dot( nn, ( lightDir ) );		
	lightDir = normalize( v );	
		
	eyeDir = normalize( iv );	
	v.x = dot( nt, ( eyeDir ) );
	v.y = dot( nb, ( eyeDir ) );
	v.z = dot( nn, ( eyeDir ) );		
	
	eyeDir = -normalize( v );		
	
	gl_TexCoord[0].xy = gl_TexCoord[0].xy * 2.0; 
	
	// Height. 	
	float height = texture2D( heightMap, gl_TexCoord[0].st).r;
	float offset  = height * 0.04 - 0.02;
	
	vec2 newTexCoord = gl_TexCoord[0].xy +  eyeDir.xy * offset;
    
    // Convert perturbed normal information stored as RGB to range [-1.0, 1.0]. 	
    vec3 bump = ( texture2D( normalMap, newTexCoord ).rgb * 2.0 ) - 1.0;    	
	
	// Normalize perturbed normal.  
	vec3 pNormal = normalize( bump );
	
	// Calculate reflection direction. 
	vec3 reflectDir = -reflect( pNormal, lightDir );	
	
	// Calculate specular parameter. 
	float spec = max( dot( eyeDir, reflectDir ), 0.0 );	
	
	// Calculate diffuse parameter.	
	// @Note: We are setting the range of [-1.0, 1.0] 
	// so that we could negate of the color component as we get from 
	// the color map. 
	float diff;
	
	diff = max( dot( pNormal, lightDir ), 0.0 );		
	
	// Calculate diffuse component. 
	vec3 diffuseColor = vec3(0.3, 0.3, 0.1) * vec3(0.8, 0.8, 0.8) * diff;
	
	vec3 diffuseColorMix = min( diffuseColor, 1.0 );	
	
	litColor = vec3( 0.8, 0.8, 0.8 ) * vec3( 0.3, 0.3, 0.3 ) * pow( spec,  10.0 ) + 
			   diffuseColorMix;
			
	// Chop off values greater then 1.0.
	litColor = min( litColor, vec3( 1.0 ) );
	
	// Set fragment color.
	gl_FragColor = vec4( litColor, 1.0 );	
	
	gl_FragColor = mix( gl_FragColor, vec4(texture2D( decalMap, newTexCoord ).rgb, 1.0 ), 0.5 );
}