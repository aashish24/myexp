// Per pixel texture coordinates.
varying vec2 texCoords;

// Normal sampler.
uniform sampler2D normals;

// Random normal sampler to general radom direction vector.
uniform sampler2D randoms;

// Depth sampler.
uniform sampler2D depths;

float temp = 1.0;

float lerp(float a, float b, float w)
{
  return (a + w * (b-a));
}


float calculateSsao(vec2 screenTC, vec2 screenSize)
{
  vec2  rotationTC = (screenTC * screenSize) / 4.0;

  vec3  rotationVector = normalize(2 * texture2D(randoms, rotationTC).xyz - 1.0);

  float screenDepthP = texture2D(depths, screenTC).z * 1000;

  const int numSamples = 16;
  float offsetScale = 0.01;
  const float offsetScaleStep = 1 + 1.1/numSamples;

  float ao = 0.0;

  const vec3 kernel[8] =
  {
  normalize(vec3(-1, -1, -1)),
  normalize(vec3(-1, -1, 1)),
  normalize(vec3(-1, 1, -1)),
  normalize(vec3(-1, 1, 1)),
  normalize(vec3( 1, -1, -1)),
  normalize(vec3( 1, -1, 1)),
  normalize(vec3( 1, 1, -1)),
  normalize(vec3( 1, 1, 1))
  };

 int actualNumberOfSamples = 0;
 for( int i = 0; i < numSamples; i++ )
   {
    vec3 offsetVector = (kernel[i % 8]) * (offsetScale *= offsetScaleStep);

    vec3 rotatedOffsetVector = reflect(offsetVector, rotationVector).xyz;

    vec3 samplePos = vec3(screenTC, screenDepthP);

    samplePos += vec3(rotatedOffsetVector.xy, rotatedOffsetVector.z * screenDepthP * 2.0);

    if(samplePos.x < 0 || samplePos.x > 1.0 || samplePos.y < 0 || samplePos.y > 1.0 ||
       texture2D(depths, samplePos.xy).z == 0.0)
      {
      // Do nothing.
      }
    else
      {
      float screenDepthS = texture2D(depths, samplePos.xy).z * 1000;

      float rangeIsInvalid = clamp( (screenDepthP - screenDepthS)/ (screenDepthS), 0.0, 1.0 );

      ao += lerp(abs(screenDepthS) < abs(samplePos.z), 0.5, rangeIsInvalid);

      actualNumberOfSamples++;
      }
   }

  ao = (ao / actualNumberOfSamples);

  ao = clamp((ao * ao + ao), 0.0, 1.0);
  return ao;
}


void main()
{
//  gl_FragColor = vec4(texture2D(depths, texCoords).xyz, 1.0);
  gl_FragData[0] = vec4(vec3(1 - calculateSsao(texCoords, vec2(800, 600))), 1.0);
//  calculateSsao(texCoords, vec2(800, 600));
//  gl_FragColor = vec4(temp, 0.0, 0.0, 1.0 );
}
