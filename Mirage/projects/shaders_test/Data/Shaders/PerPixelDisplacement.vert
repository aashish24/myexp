
uniform   vec3   uLightPos;
uniform   float  uBumpDepth;
   
attribute vec3   tangent;
attribute vec3   binormal;

varying   vec3   tangentLightVec;
varying   vec3   tangentEyeVec;

varying   vec3   testNormal;

void main()
{
  vec3 lightVec;	
	vec3 eyeVec;	
	
	gl_Position = ftransform();	
		
	gl_TexCoord[0] = gl_MultiTexCoord0;	
	
	testNormal = gl_Normal;
	
	vec3 eyeDir = vec3( gl_ModelViewMatrix * gl_Vertex );
	
	vec3 t;
	vec3 b;
	vec3 n;
	
	if( testNormal.x != 1.0 )
	{
	  t = vec3(1.0, 0.0, 0.0);
	  b = vec3(0.0, 1.0, 0.0);
	  n = vec3(0.0, 0.0, 1.0);
	}
	else
	{
	  t = vec3(1.0, 0.0, 0.0);
	  b = vec3(0.0, 1.0, 0.0);
	  n = vec3(0.0, 0.0, 1.0);
	  //t = vec3(0.0, 0.0, -1.0);
	  //b = vec3(0.0, 1.0,  0.0);
	  //n = vec3(1.0, 0.0,  0.0);
	}
		
	t  = normalize( gl_NormalMatrix * t );
	n  = normalize( gl_NormalMatrix * n );
	b  = normalize( gl_NormalMatrix * b );		

	vec3 lightPos =  vec4( uLightPos, 1.0 ).xyz;
		
	lightVec.x = dot( t, ( lightPos ) );
	lightVec.y = dot( b, ( lightPos ) );
	lightVec.z = dot( n, ( lightPos ) );	
	
	tangentLightVec = lightVec;
		
	eyeVec.x = dot( eyeDir, t );
	eyeVec.y = dot( eyeDir, b );
	eyeVec.z = dot( eyeDir, n ) * ( 1.0 / uBumpDepth );	
	
	tangentEyeVec = eyeVec;		
	
	gl_FrontColor     = gl_FrontLightModelProduct.sceneColor;
}


