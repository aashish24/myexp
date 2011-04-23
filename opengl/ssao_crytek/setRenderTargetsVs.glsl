
varying vec3 normal;
varying vec4 color;
varying vec2 depthPos;
varying vec4 viewSpacePos;


void main()
{
   vec4 finalPos = gl_ModelViewProjectionMatrix * gl_Vertex;
   viewSpacePos = gl_ModelViewMatrix * gl_Vertex;

   normal = gl_NormalMatrix * gl_Normal;
   color = gl_Color;

   depthPos.x = finalPos.z;
   depthPos.y = finalPos.w;

   gl_Position = finalPos;
}
