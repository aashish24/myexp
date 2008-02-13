
uniform sampler3D baseTexture;
uniform float sampleDensity;
uniform float transparency;
uniform float alphaCutOff;

varying vec3 deltaTexCoord;
varying vec3 texcoord;

void main(void) 
{
	vec3 texcoord2 = texcoord;
	 
    vec3 deltaTexCoord2 = normalize(deltaTexCoord)*sampleDensity; 

    vec4 glFragColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 color = texture3D( baseTexture, texcoord2 ); 
    
    /*while (texcoord2.x>=0.0 && texcoord2.x<=1.0 &&
           texcoord2.y>=0.0 && texcoord2.y<=1.0 &&
           texcoord2.z>=0.0 && texcoord2.z<=1.0)
    {    
       vec4 color = texture3D( baseTexture, texcoord2 );
       float r = color[3]*transparency;
       if (r>alphaCutOff)
       {
         glFragColor.xyz = glFragColor.xyz*(1.0-r)+color.xyz*r;
         glFragColor.w += r;
       }	
		
		
       texcoord2 += deltaTexCoord2; 
    }
    //if (glFragColor.w>1.0) glFragColor.w = 1.0; 
    
    vec4 colorf  = glFragColor;
    if( colorf.w > 1.0 )
    {
		colorf.w = 1.0;		
    }    
   
	
    if( colorf.w == 0.0 )
    {
		discard;
    }
    else
    {
		gl_FragColor = colorf;
	}*/
	
	if( ( color.x == 0.0 ) && ( color.y == 0.0 ) && ( color.z == 0.0 ) )
	{
		discard;		
	}
	else
	{
		gl_FragColor = color;	
	}		
}