
void main()
{
   // 1) Color target, 2) normal target, 3) depth target.

   gl_FragData[0] = vec4(0.0, 0.0, 0.0, 1.0);
   gl_FragData[1] = vec4(0.5z, 0.5, 0.5, 1.0);
   gl_FragData[2] = vec4(1.0, 1.0, 1.0, 1.0);
}
