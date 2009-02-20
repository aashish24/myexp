
uniform float   uEtaR;
uniform float   uEtaG;
uniform float   uEtaB;

uniform float   uFresnelPower;

const float   F               = ( ( 1.0 - uEtaG ) * ( 1.0 - uEtaG ) ) / ( ( 1.0 + uEtaG ) * ( 1.0 + uEtaG ) );

varying vec3  reflectR;

varying vec3  refractRR;
varying vec3  refractRG;
varying vec3  refractRB;

varying float ratio;

void main(void) 
{
    gl_Position    = ftransform();
    
    vec3 normal    = normalize( gl_NormalMatrix * gl_Normal );
    
    vec4 pos4      = gl_ModelViewMatrix * gl_Vertex;
    vec3 pos3      = pos4.xyz / pos4.w;
    vec3 i         = normalize( pos3 );
    vec3 n         = normal;
    
    ratio          = max( 0.0, min( 1.0, F + ( 1.0 - F ) * pow( ( 1.0 - dot( -i, n ) ), uFresnelPower ) ) );
    
    refractRR      = refract( i, n, uEtaR );
    refractRR      = vec3( gl_TextureMatrix[0] * vec4( refractRR, 1.0 ) );
    
    refractRG      = refract( i, n, uEtaG );
    refractRG      = vec3( gl_TextureMatrix[0] * vec4( refractRG, 1.0 ) );
    
    refractRB      = refract( i, n, uEtaB );
    refractRB      = vec3( gl_TextureMatrix[0] * vec4( refractRB, 1.0 ) );
    
    reflectR       = reflect( i, n );
    reflectR       = vec3( gl_TextureMatrix[0] * vec4( reflectR, 1.0 ) );
}
