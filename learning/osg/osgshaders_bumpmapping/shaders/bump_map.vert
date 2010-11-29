
// Precalculated binormal and tangent vectors. 


// Light direction in tangent space. 
//varying vec3 lightDir;

// Eye direction in tangent space. 
//varying vec3 eyeDir;

// Normalized and interpolated tangent, binormal and normal. 
varying vec3 t;
varying vec3 b;
varying vec3 n;

varying vec3 iv; 
varying vec3 il;

//varying vec3 vForLight; 

// Entry function. 
void main()
{
	// Transformed position of the vertex. 
	gl_Position = ftransform();	
	
	// Store texture coordinate. 
	gl_TexCoord[0]  = gl_MultiTexCoord0;	

	// Eye direction for each vertex in eye space. 
	//eyeDir = vec3( gl_ModelViewMatrix * gl_Vertex );

	iv = vec3( gl_ModelViewMatrix * gl_Vertex );
	il = gl_LightSource[0].position.xyz;	
}



