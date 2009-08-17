varying vec3 n;
varying vec3 v;

void main()
{
	vec3 l			 	= normalize( gl_LightSource[0].position.xyz - v );
	vec3 e				= normalize( -v );
	vec3 r				= normalize( -reflect( l, n ) ); 	
	
	float t				= dot( e, r ); 
	
	vec4 amb 			= gl_FrontLightProduct[0].ambient;
	vec4 diff			= gl_FrontLightProduct[0].diffuse * max( dot( l, n ), 0.0 );	
	vec4 spec			= ( ( gl_FrontLightProduct[0].specular * t ) / ( gl_FrontMaterial.shininess -  ( t * gl_FrontMaterial.shininess ) + t ) );
	
	gl_FragColor 		= gl_FrontLightModelProduct.sceneColor + amb + diff + spec;
}
