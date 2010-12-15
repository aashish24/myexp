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
   vec3 n = normalize(normal);
   float depthVal = depthPos.x / depthPos.y;

   gl_FragData[0] = color;
   gl_FragData[1] = vec4(((n + 1.0) * 0.5), 1.0);
   gl_FragData[2] = vec4(depthVal, depthVal, depthVal, depthVal);
}
