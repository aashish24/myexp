
varying vec3 L1;
varying vec3 L2;
varying vec3 L3;

// Normal at each pixel. 
varying vec3 N;

// Eye vector at each pixel.
varying vec3 E;

// Reflection vector at each pixel. 
varying vec3 R1;
varying vec3 R2;
varying vec3 R3;

varying vec3 v;

void main(void)
{
	L1 = normalize( L1 );
	L2 = normalize( L2 );
	L3 = normalize( L3 );
	
	E = normalize( E );
	N = normalize( N ); 
	
	R1 = reflect( -L1, N );		
	R2 = reflect( -L2, N );
	R3 = reflect( -L3, N );
		
	// Diffuse light calculations. 
	vec4 diff = gl_FrontLightProduct[0].diffuse * max( dot( N,L1 ), 0.0 );  
	diff = clamp( diff, 0.0, 1.0 ); 

	
	vec4 diff2 = gl_FrontLightProduct[1].diffuse * max( dot( N,L2 ), 0.0 );  
	diff2 = clamp( diff2, 0.0, 1.0 ); 

	vec3 pos = gl_LightSource[1].position.xyz;
	vec3 oglPos;
	oglPos[ 2 ] = -pos[1];
	oglPos[ 1 ] = pos[2];	
	vec3 L3 = normalize( oglPos - v );   
	vec4 diff3 = gl_FrontLightProduct[2].diffuse * max( dot( N, L3 ), 0.0 );  
	diff3 = clamp( diff3, 0.0, 1.0 ); 
	
    diff = clamp( ( diff+ diff2 + diff3 ), 0.0, 1.0 ); 

	// Specular light calculations. 
	float specular = pow( max( dot( R1, E ), 0.0), 30.0 );
	float spec = gl_LightSource[0].specular * gl_FrontMaterial.specular * specular;	
	spec = clamp( spec, 0.0, 1.0 );
	
	specular = pow( max( dot( R2, E ), 0.0), 30.0 );
	float spec2 = gl_LightSource[1].specular * gl_FrontMaterial.specular * specular;	
	spec2 = clamp( spec2, 0.0, 1.0 );
	
	specular = pow( max( dot( R3, E ), 0.0), 30.0 );
	float spec3 = gl_LightSource[2].specular * gl_FrontMaterial.specular * specular;	
	spec3 = clamp( spec3, 0.0, 1.0 );
	
	spec = clamp( ( spec + spec2 + spec3 ), 0.0, 1.0 ); 
	
	gl_FragColor = gl_FrontLightModelProduct.sceneColor + diff + spec;
}