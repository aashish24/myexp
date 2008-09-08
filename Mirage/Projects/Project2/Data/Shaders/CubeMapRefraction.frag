
uniform float       uMixRatio;
uniform samplerCube uCubeMap;

varying vec3        normal;
varying vec3        normalInWorldSpace;

varying vec3        eyeDir;
varying float       lightIntensity;

void main (void)
{
    vec3 r          = refract( eyeDir, normal, 0.66 );    
	vec3 color		= vec3( textureCube( uCubeMap, r ));
	  
    vec3 base       = vec3( lightIntensity * gl_FrontMaterial.diffuse );
    color           = mix( color, base, uMixRatio );

    gl_FragColor    = vec4 ( color, 1.0 );
}
