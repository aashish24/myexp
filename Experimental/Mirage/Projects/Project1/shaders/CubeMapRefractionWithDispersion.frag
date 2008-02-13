
uniform samplerCube uCubeMap;

varying vec3        reflectR;

varying vec3        refractRR;
varying vec3        refractRG;
varying vec3        refractRB;

varying float       ratio;

void main (void)
{
    vec3 refractColor, reflectColor;
    
    refractColor.r    = vec3( textureCube( uCubeMap, refractRR ) ).r;
    refractColor.g    = vec3( textureCube( uCubeMap, refractRG ) ).g;
    refractColor.b    = vec3( textureCube( uCubeMap, refractRB ) ).b;
    
    reflectColor      = vec3( textureCube( uCubeMap, reflectR ) );
    
    vec3 color        = mix( refractColor, reflectColor, ratio );
    
    gl_FragColor      = vec4( color, 1.0 );
}
