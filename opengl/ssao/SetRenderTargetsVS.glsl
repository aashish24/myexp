/*
   Set Render Targets for Deferred Shading - OpenGL
   Game Graphics Programming
   Created by Allen Sherrod
*/


varying vec3 normal;
varying vec4 color;
varying vec2 depthPos;


void main()
{
   vec4 finalPos = gl_ModelViewProjectionMatrix * gl_Vertex;

   normal = gl_NormalMatrix * gl_Normal;
   color = gl_Color;
   
   depthPos.x = finalPos.z;
   depthPos.y = finalPos.w;

   gl_Position = finalPos;
}
