
varying float		  lightIntensity; 
varying vec3		  position;

uniform vec3		  Offset;
uniform sampler3D	sampler3d;
uniform sampler2D	texture;  

varying vec3      texCoord;


uniform int show;

void main (void)
{	
	show = 1;
	vec4 noisevec;
	vec4 decal;

	vec3 color;
	float intensity;

	noisevec = texture3D( sampler3d, 1.2 * ( vec3 ( 0.5 ) + position ) );
	decal    = texture2D( texture, texCoord.xyz );

	intensity = 0.75 * ( noisevec.x + noisevec.y + noisevec.z + noisevec.w );


	intensity = 1.95 * abs( 2.0 * intensity - 1.0 );
	intensity = clamp( intensity, 0.0, 1.0 );

  if( show )
  {
    if ( intensity > Offset.x ) discard;
  }
  else
  {
   if ( intensity <= Offset.x ) discard;
  }

  //gl_FragColor = vec4 ( vec4( 0.2, 0.5, 0.5, 1.0 ) );  
  
  gl_FragColor = vec4 ( decal );
}
