
varying vec2 texCoords;

uniform sampler2D colors;
uniform sampler2D normals;
uniform sampler2D depths;

uniform sampler2D randoms;

uniform vec3 lightPos;
uniform vec4 lightColor;

vec2 g_screen_size = vec2(800, 600);

float random_size = 64.0;
float g_sample_rad = 0.01;
float g_intensity = 1.5;
float g_scale = 2.0;
float g_bias = 0.1;

vec4 getPosition(vec2 uv)
{
  float depthVal = texture2D(depths, uv).r;

  // Calculate world-space position from depth.
  vec4 position;
  position.xy = texCoords * 2.0 - 1.0;
  position.z = depthVal;
  position.w = 1.0;

  // Transform position to world space.
  vec4 newPosition = gl_ModelViewProjectionMatrixInverse * position;
  newPosition /= newPosition.w;

  return newPosition;
}

vec3 getNormal(vec2 uv)
{
 return normalize(texture2D(normals, uv).xyz * 2.0 - 1.0);
}

vec2 getRandom(vec2 uv)
{
  return normalize(texture2D(randoms, g_screen_size * uv / random_size).xy * 2.0 - 1.0);
}

float doAmbientOcclusion(vec2 tcoord, vec2 uv, vec3 p, vec3 cnorm)
{
 vec3 diff = vec3(getPosition(tcoord + uv)) - p;
 vec3 v = normalize(diff);
 float d = length(diff)*g_scale;
 return max(0.1,dot(cnorm,v)-g_bias)*(1.0/(1.0+d))*g_intensity;
}

float processAmbientOcclusion()
{
  vec2 vec[4];
  vec[0] = vec2(1,0);
  vec[1] = vec2(-1,0);
  vec[2] = vec2(0,1);
  vec[3] = vec2(0,-1);

  vec3 p = vec3(getPosition(texCoords));
  vec3 n = getNormal(texCoords);
  vec2 rand = getRandom(texCoords);

 float ao = 0.0;
 float rad = g_sample_rad/p.z;

 //**SSAO Calculation**//
 int iterations = 4;
 for (int j = 0; j < iterations; ++j)
 {
  vec2 coord1 = reflect(vec[j],rand)*rad;
  vec2 coord2 = vec2(coord1.x*0.707 - coord1.y*0.707,
              coord1.x*0.707 + coord1.y*0.707);

  ao += doAmbientOcclusion(texCoords,coord1*0.25, p, n);
  ao += doAmbientOcclusion(texCoords,coord2*0.5, p, n);
  ao += doAmbientOcclusion(texCoords,coord1*0.75, p, n);
  ao += doAmbientOcclusion(texCoords,coord2, p, n);
 }

 ao/= iterations*4.0;

 return ao;
}

void main()
{
  vec4 col = texture2D(colors, texCoords);

//   gl_FragColor = (col + lightColor) * (1 - processAmbientOcclusion());

  float ao = 1 - processAmbientOcclusion();

  gl_FragColor = vec4(ao, ao, ao, 1.0);

//  vec4 col = texture2D(depths, texCoords);

//  gl_FragColor = col;
}
