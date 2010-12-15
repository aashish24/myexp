/*
   Deferred Shading Directional Light - OpenGL
   Game Graphics Programming
   Created by Allen Sherrod
*/


varying vec2 texCoords;

uniform sampler2D colors;
uniform sampler2D normals;
uniform sampler2D depths;

uniform vec3 lightPos;
uniform vec4 lightColor;


void main()
{
   vec4 col = texture2D(colors, texCoords);
   vec4 norm = texture2D(normals, texCoords);
   float depthVal = texture2D(depths, texCoords).r;

   // Unpack into -1, 1 range.
   norm = norm * 2.0 - 1.0;

   // Calculate world-space position from depth.
   vec4 position;
   position.xy = texCoords * 2.0 - 1.0;
   position.z = depthVal;
   position.w = 1.0;

   // Transform position to world space.
   position = gl_ModelViewMatrixInverse * position;
   position /= position.w;

   vec3 lightVec = normalize(lightPos - position.xyz);
   float diffuse = clamp(dot(norm.xyz, lightVec), 0.0, 1.0);

   gl_FragColor = (col + lightColor) * diffuse;
}
