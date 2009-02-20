varying vec3 N;
varying vec3 E;
varying vec3 L1;
varying vec3 L2;
varying vec3 L3;

varying vec3 v;

void main( void )
{
   v = vec3( gl_ModelViewMatrix * gl_Vertex );       
   N = normalize( gl_NormalMatrix  * gl_Normal );
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
   
   L1 = vec4( gl_LightSource[0].position.xyz - v, 1.0  );
   L2 = vec4( gl_LightSource[1].position.xyz - v , 1.0 );
   L3 = vec4( gl_LightSource[2].position.xyz - v , 1.0 );
   E = -v;
 }
          