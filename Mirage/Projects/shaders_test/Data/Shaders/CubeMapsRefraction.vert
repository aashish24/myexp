

uniform vec3  uLightPos;
uniform vec3  uEyePos;

uniform float uEta;
uniform float uFresnelPower;

const float   F             = ( ( 1.0 - uEta ) * ( 1.0 - uEta ) ) / ( ( 1.0 + uEta ) * ( 1.0 + uEta ) );

varying vec3  reflectR;
varying vec3  refractR;
varying float ratio;

varying vec3  eyePos;

void main(void) 
{
    gl_Position    = ftransform();
    
    vec3 normal    = normalize( gl_NormalMatrix * gl_Normal );
    
    vec4 pos4      = gl_ModelViewMatrix * gl_Vertex;
    vec3 pos3      = pos4.xyz;
    
    pos3           = vec3( gl_Vertex ) - uEyePos;
    
        
    vec3 i         = normalize( pos3 );
    vec3 n         = normal;
    
    eyePos         = uEyePos;
    
    ratio          = max( 0.0, min( 1.0, F + ( 1.0 - F ) * pow( ( 1.0 - dot( -i, n ) ), uFresnelPower ) ) );    
    
    refractR       = refract( i, n, 1.0 );
    //refractR       = vec3( gl_TextureMatrix[0] * vec4( refractR, 1.0 ) );
    
    reflectR       = reflect( i, n );
    //reflectR       = vec3( gl_TextureMatrix[0] * vec4( reflectR, 1.0 ) );
}
