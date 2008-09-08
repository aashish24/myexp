
uniform sampler2D uNormalMap;
uniform sampler3D uDistanceMap;
uniform sampler2D uBaseMap;

varying	vec3      tangentLightVec;
varying	vec3      tangentEyeVec;

varying vec3      testNormal;

void main()
{   
  // Normalize the vectors.   
  tangentEyeVec   = normalize( tangentEyeVec );
  tangentLightVec = normalize( tangentLightVec );      	
  
  vec3 offset = tangentEyeVec * vec3( 16.0 / 256.0, 16.0 / 256.0, 1.0 );
    
  // Assume that surface is locally planar.   
  
  vec3 point;
  
  //if( testNormal.x == 1.0 )
  //{  
    //point = vec3( 1.0, gl_TexCoord[0].yz );
  //}
  //else
  //{
    point = vec3( gl_TexCoord[0].xyz );
  //}
  
  for( int i = 0; i < 64; ++i )
  {
    float distance = texture3D( uDistanceMap, point ).r;    
    point = point + distance * offset;
  }
  
  vec3 test =  texture3D(  uDistanceMap, vec3( 0.1, gl_TexCoord[0].yz )  ).rgb;
  
  vec3 normal  = ( texture2D( uNormalMap, point.xy ).rgb * 2.0 ) - 1.0;	
	vec3 pNormal = normalize( normal );		  
  
  float diff = max( dot( pNormal, tangentLightVec ), 0.0 );    
  
  vec3 r = normalize( -reflect( offset, pNormal ) ); 	
  
  vec4 spec			= gl_FrontLightProduct[0].specular * pow( max( dot( r, tangentEyeVec ), 0.0 ), 0.3 * gl_FrontMaterial.shininess );
  
  vec3 color = texture2D( uBaseMap, point.xy ).rgb;
  
  vec3  litColor = color * diff + spec.xyz + gl_FrontLightProduct[0].ambient;; 
	
	 //gl_FragColor = vec4( litColor, 1.0 );
		
	
	if( ( point.z > 0.99 ) )
	{
	  gl_FragColor = vec4( 0.4, 0.4, 0.4, 0.0 );	  
	}
	else
	{
	  gl_FragColor = vec4( litColor, 1.0 );  
	}	
}

