
varying vec3  normal;
varying vec3  eyeDir;
varying float lightIntensity;

uniform vec3  uLightPos;

void main(void) 
{
    normal         = normalize( gl_NormalMatrix * gl_Normal );
    vec4 pos       = gl_ModelViewMatrix * gl_Vertex;
    eyeDir         = pos.xyz;
    lightIntensity = max( dot( normalize( uLightPos - eyeDir ), normal ), 0.0 );
    gl_Position    = ftransform();
 }
