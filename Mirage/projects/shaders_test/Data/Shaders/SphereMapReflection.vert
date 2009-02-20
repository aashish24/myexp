
void main(void) 
{
    gl_Position       = ftransform();
    vec3 normal       = normalize( gl_NormalMatrix * gl_Normal );
    vec4 pos          = gl_ModelViewMatrix * gl_Vertex;
    vec3 eyeDir       = pos.xyz;
    
    // Since the diretion to the eye is ( 0, 0, 1 ) in sphere map's space we need to make sure
    // that outr reflection vector is normalized as all the subsequent equations based on this. 
    // The normal would then only be ( rx, ry, rz + 1 ) that is normalize( eyeDir + reflectionDir )
    vec3 reflectDir   = normalize( reflect( eyeDir , normal ) );    
    
    gl_TexCoord[0]    = gl_MultiTexCoord0;
    
    float sNew        = ( reflectDir.x / sqrt( ( reflectDir.x * reflectDir.x ) + ( reflectDir.y * reflectDir.y ) + ( ( reflectDir.z + 1.0 ) *  ( reflectDir.z + 1.0 ) ) ) );
    float tNew        = ( reflectDir.y / sqrt( ( reflectDir.x * reflectDir.x ) + ( reflectDir.y * reflectDir.y ) + ( ( reflectDir.z + 1.0 ) *  ( reflectDir.z + 1.0 ) ) ) );
    
    sNew              = ( sNew / 2.0 ) + 0.5;
    tNew              = ( tNew / 2.0 ) + 0.5;
    
    gl_TexCoord[0].s  = sNew;
    gl_TexCoord[0].t  = tNew;    
}
