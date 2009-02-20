
// Per pixel normal. 
varying vec3 n;

// Pixel location. 
varying vec3 v;

// Per pixel half vector. 
varying vec3 h;

void main()
{
  // Light vector. 
	vec3 l = normalize( gl_LightSource[0].position.xyz - v );		
	
	vec4 ambi = gl_FrontLightProduct[0].ambient;
	vec4 diff	= gl_FrontLightProduct[0].diffuse * max( dot( l, n ), 0.0 );	
	vec4 spec	= gl_FrontLightProduct[0].specular * pow( max( dot( n, h ), 0.0 ), 0.3 * gl_FrontMaterial.shininess );
	
	// Final color of the pixel. 
	gl_FragColor 		= gl_FrontLightModelProduct.sceneColor + ambi + diff + spec;
}
