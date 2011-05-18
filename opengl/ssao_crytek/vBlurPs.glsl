uniform sampler2D scene; // the texture with the scene you want to blur
uniform sampler2D normals;
uniform sampler2D depths;

varying vec2 vTexCoord;

const float blurSize = 1.0/800.0; // I've chosen this size because this will result in that every step will be one pixel wide if the scene texture is of size 512x512

float calculateGaussianWeight(float standardDeviation, float distance)
{
  float gw = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
             exp( -pow( distance, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );

  return gw;
}

void main(void)
{
   vec4 sum = vec4(0.0);

   float standardDeviation = 2.0;
   float d1 = vTexCoord.y - 4.0*blurSize;
   float d2 = vTexCoord.y - 3.0*blurSize;
   float d3 = vTexCoord.y - 2.0*blurSize;
   float d4 = vTexCoord.y - 1.0*blurSize;
   float d5 = vTexCoord.y + 1.0*blurSize;
   float d6 = vTexCoord.y + 2.0*blurSize;
   float d7 = vTexCoord.y + 3.0*blurSize;
   float d8 = vTexCoord.y + 4.0*blurSize;

   // take nine samples, with the distance blurSize between them
   sum += texture2D(scene, vec2(vTexCoord.x, d1)) * calculateGaussianWeight(2.0, 4.0);
   sum += texture2D(scene, vec2(vTexCoord.x, d2)) * calculateGaussianWeight(2.0, 3.0);
   sum += texture2D(scene, vec2(vTexCoord.x, d3)) * calculateGaussianWeight(2.0, 2.0);
   sum += texture2D(scene, vec2(vTexCoord.x, d4)) * calculateGaussianWeight(2.0, 1.0);
   sum += texture2D(scene, vec2(vTexCoord.x, vTexCoord.y)) * calculateGaussianWeight(2.0, 0.0);
   sum += texture2D(scene, vec2(vTexCoord.x, d5)) * calculateGaussianWeight(2.0, -1.0);
   sum += texture2D(scene, vec2(vTexCoord.x, d6)) * calculateGaussianWeight(2.0, -2.0);
   sum += texture2D(scene, vec2(vTexCoord.x, d7)) * calculateGaussianWeight(2.0, -3.0);
   sum += texture2D(scene, vec2(vTexCoord.x, d8)) * calculateGaussianWeight(2.0, -4.0);

   gl_FragData[0] = sum;
}
