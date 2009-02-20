
varying vec3 texcoord;
varying vec3 deltaTexCoord;
            
void main(void)
{
    texcoord = gl_MultiTexCoord0.xyz;
    gl_Position     = ftransform();  
    deltaTexCoord = normalize( gl_ModelViewMatrixInverse * vec4(0,0,0,1) - gl_Vertex );
}


