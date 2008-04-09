
void main()
{
	gl_Position = ( gl_ModelViewProjectionMatrix * gl_Vertex );
	
	// Vertex position in eye space. 
	vec3 v = vec3( gl_ModelViewMatrix * gl_Vertex );
	
	// Per vertex normal in eye space. 
	vec3 n = normalize( gl_NormalMatrix * gl_Normal );	
	
	// Light vector. 
	vec3 l = normalize( gl_LightSource[0].position.xyz - v );
	
	// Eye vector. 
	vec3 e = normalize( -v );
	
	// Reflection. 
	vec3 r = normalize( -reflect( l, n ) ); 
	
	vec4 ambi = gl_FrontLightProduct[0].ambient;
	vec4 diff	= gl_FrontLightProduct[0].diffuse * max( dot( l, n ), 0.0 );	
	vec4 spec	= gl_FrontLightProduct[0].specular * pow( max( dot( r, e), 0.0 ), 0.3 * gl_FrontMaterial.shininess );
	
	gl_FrontColor = gl_FrontLightModelProduct.sceneColor + ambi + diff + spec;	
} 
