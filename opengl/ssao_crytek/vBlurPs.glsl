uniform sampler2D sceneSampler; // the texture with the scene you want to blur
varying vec2 vTexCoord;

const float blurSize = 1.0/800.0; // I've chosen this size because this will result in that every step will be one pixel wide if the sceneSampler texture is of size 512x512

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

   float gw1 = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
               exp( -pow( 4, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );
   float gw2 = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
               exp( -pow( 3, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );
   float gw3 = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
               exp( -pow( 2, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );
   float gw4 = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
               exp( -pow( 1, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );
   float gw5 = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
               exp( -pow( -1, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );
   float gw6 = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
               exp( -pow( -2, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );
   float gw7 = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
               exp( -pow( -3, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );
   float gw8 = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
               exp( -pow( -4, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );

   float gwc = 1.0 / ( sqrt( 2.0f * 3.14f ) * standardDeviation ) *
               exp( -pow( 0.0, 2.0f ) / ( 2.0f * pow( standardDeviation, 2.0f ) ) );


   // take nine samples, with the distance blurSize between them
   sum += texture2D(sceneSampler, vec2(vTexCoord.x, d1)) * gw1;
   sum += texture2D(sceneSampler, vec2(vTexCoord.x, d2)) * gw2;
   sum += texture2D(sceneSampler, vec2(vTexCoord.x, d3)) * gw3;
   sum += texture2D(sceneSampler, vec2(vTexCoord.x, d4)) * gw4;
   sum += texture2D(sceneSampler, vec2(vTexCoord.x, vTexCoord.y)) * gwc;
   sum += texture2D(sceneSampler, vec2(vTexCoord.x, d5)) * gw5;
   sum += texture2D(sceneSampler, vec2(vTexCoord.x, d6)) * gw6;
   sum += texture2D(sceneSampler, vec2(vTexCoord.x, d7)) * gw7;
   sum += texture2D(sceneSampler, vec2(vTexCoord.x, d8)) * gw8;

   gl_FragData[0] = sum;
}
