
uniform samplerCube uCubeMap;

varying vec3        reflectR;
varying vec3        refractR;
varying float       ratio;
varying vec3        eyePos;

void main (void)
{
    vec3 refractColor = vec3( textureCube( uCubeMap, refractR ) );
    vec3 reflectColor = vec3( textureCube( uCubeMap, reflectR ) );
    
    vec3 color        = mix( refractColor, reflectColor, ratio );
    
    gl_FragColor      = vec4( color, 1.0 );
}
