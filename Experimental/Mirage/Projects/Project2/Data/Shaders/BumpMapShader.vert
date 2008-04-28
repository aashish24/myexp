
// Precalculated binormal and tangent vectors. 

attribute vec3 tangent;
attribute vec3 binormal;
attribute vec3 normal;

// Light direction in tangent space. 
varying vec3 lightDir;

// Eye direction in tangent space. 
varying vec3 eyeDir;

// Normalized and interpolated tangent, binormal and normal. 
varying vec3 t;
varying vec3 b;
varying vec3 n;

varying vec3 vForLight; 

// Entry function. 
void main()
{
	// Transformed position of the vertex. 
	gl_Position = ftransform();	
	
	// Store texture coordinate. 
	gl_TexCoord[0]  = gl_MultiTexCoord0;	

	// Eye direction for each vertex in eye space. 
	eyeDir = vec3( gl_ModelViewMatrix * gl_Vertex );

	// Normalized t, b and n vector. 	
	t = normalize( gl_NormalMatrix * tangent );	
	b = normalize( gl_NormalMatrix * binormal );
	n = normalize( gl_NormalMatrix * normal );				

	vForLight = vec3( gl_ModelViewMatrix * gl_Vertex );
	
	//vec3 lightPos =  vec4( gl_LightSource[0].position.xyz, 1.0 ).xyz;
	
	// Temporary vector for calculation purposes. 
	vec3 v;	
	
	// Calculating and storing light direction in tangent space. 
	vec3 lightPos = normalize( ( gl_LightSource[0].position.xyz ) - eyeDir );
	
	//  
	eyeDir = -normalize( eyeDir );
	
	//v.x = dot( t, ( gl_LightSource[0].position.xyz ) );
	//v.y = dot( b, ( gl_LightSource[0].position.xyz ) );
	//v.z = dot( n, ( gl_LightSource[0].position.xyz ) );	
	
	v.x = dot( t, ( lightPos ) );
	v.y = dot( b, ( lightPos ) );
	v.z = dot( n, ( lightPos ) );	
	
	//v.x = dot( t, vec3( 0.0, 0.0, 10.0 ) );
	//v.y = dot( b, vec3( 0.0, 0.0, 10.0 ) );
	//v.z = dot( n, vec3( 0.0, 0.0, 10.0 ) );
	
	
	// Normalize tangent space light direction. 
	lightDir = normalize( v );

	// Calculate and store eye direction in tangent space. 
	v.x = dot( eyeDir, t );
	v.y = dot( eyeDir, b );
	v.z = dot( eyeDir, n );	

	// Normalize tangent space eye direction. 
	eyeDir = normalize( v );	
}



