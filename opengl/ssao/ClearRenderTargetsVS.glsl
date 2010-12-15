/*
   Clear Rendering Targets for Deferred Shading - OpenGL
   Game Graphics Programming
   Created by Allen Sherrod
*/


void main()
{
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
