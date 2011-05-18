uniform sampler2D scene; // the texture with the scene you want to blur
uniform sampler2D depths;
uniform sampler2D normals;

varying vec2 vTexCoord;

const float blurSize = 1.0/800.0; // I've chosen this size because this will result in that every step will be one pixel wide if the scene texture is of size 512x512

float totalWeight = 0.0;

float calculateGaussianWeight(float standardDeviation, float distance)
{
  float gw = 0.0;

  float depth = texture2D( depths, vTexCoord ).z;
  float sampleDepth = texture2D( depths, vec2( vTexCoord.x - distance * blurSize, vTexCoord.y) ).z;

  vec3 normal = texture2D( normals, vTexCoord ).xyz;
  vec3 sampleNormal = texture2D( normals, vec2( vTexCoord.x - distance * blurSize, vTexCoord.y) ).xyz;

  if( abs( depth - sampleDepth ) < 0.1 || dot( normal, sampleNormal ) > 0.8 )
  {
    gw = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
         exp( -pow( distance, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );
  }

  totalWeight += gw;

  return gw;
}

void main(void)
{
   vec4 sum = vec4(0.0);

   float standardDeviation = 3.0;

   float d1 = vTexCoord.x - 4.0*blurSize;
   float d2 = vTexCoord.x - 3.0*blurSize;
   float d3 = vTexCoord.x - 2.0*blurSize;
   float d4 = vTexCoord.x - 1.0*blurSize;
   float d5 = vTexCoord.x + 1.0*blurSize;
   float d6 = vTexCoord.x + 2.0*blurSize;
   float d7 = vTexCoord.x + 3.0*blurSize;
   float d8 = vTexCoord.x + 4.0*blurSize;

   // take nine samples, with the distance blurSize between them
   sum += texture2D(scene, vec2(d1, vTexCoord.y)) * calculateGaussianWeight(2.0, 4.0);
   sum += texture2D(scene, vec2(d2, vTexCoord.y)) * calculateGaussianWeight(2.0, 3.0);
   sum += texture2D(scene, vec2(d3, vTexCoord.y)) * calculateGaussianWeight(2.0, 2.0);
   sum += texture2D(scene, vec2(d4, vTexCoord.y)) * calculateGaussianWeight(2.0, 1.0);
   sum += texture2D(scene, vec2(vTexCoord.x, vTexCoord.y)) * calculateGaussianWeight(2.0, 0.0);
   sum += texture2D(scene, vec2(d5, vTexCoord.y)) * calculateGaussianWeight(2.0, -1.0);
   sum += texture2D(scene, vec2(d6, vTexCoord.y)) * calculateGaussianWeight(2.0, -2.0);
   sum += texture2D(scene, vec2(d7, vTexCoord.y)) * calculateGaussianWeight(2.0, -3.0);
   sum += texture2D(scene, vec2(d8, vTexCoord.y)) * calculateGaussianWeight(2.0, -4.0);

   gl_FragData[0] = sum / totalWeight;
}
