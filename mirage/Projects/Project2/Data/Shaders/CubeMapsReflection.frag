
uniform float       uMixRatio;

uniform samplerCube uCubeMap;

varying vec3        normal;
varying vec3        eyeDir;
varying float       lightIntensity;

void main (void)
{
    vec3 reflectDir   = reflect( eyeDir, normal );
    vec3 envColor     = vec3( textureCube( uCubeMap, reflectDir ) );
    vec3 base         = vec3( lightIntensity * gl_FrontMaterial.diffuse );
    envColor          = mix( envColor, base, uMixRatio );
    gl_FragColor      = vec4(envColor, 1.0);
}
