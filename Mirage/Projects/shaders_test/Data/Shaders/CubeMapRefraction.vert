
uniform vec3	uLightPos;
uniform vec3	uEyePos;

varying vec3  normal;

varying vec3  eyeDir;
varying float lightIntensity;

void main(void) 
{
    gl_Position		      = ftransform();
    normal  			      = normalize( gl_NormalMatrix * gl_Normal );    
          
    eyeDir 			        = vec3( gl_Vertex ) - uEyePos;
    vec4 pos            = gl_ModelViewMatrix * gl_Vertex;        
    
    lightIntensity      = max( dot( normalize( uLightPos - pos.xyz ), normal ), 0.0 );
}
