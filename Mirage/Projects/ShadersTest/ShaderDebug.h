
#ifndef __SHADER_DEBUG_H__
#define __SHADER_DEBUG_H__

///////////////////////////////////////////////////////////////////////////////
//
// Generate and print log related with the shader. 
// 
///////////////////////////////////////////////////////////////////////////////

void printShaderInfoLog( GLuint obj )
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	  glGetShaderiv( obj, GL_INFO_LOG_LENGTH,&infologLength );

    if( infologLength > 0 )
    {
        infoLog = ( char *)malloc( infologLength );
        glGetShaderInfoLog( obj, infologLength, &charsWritten, infoLog );
        
        #ifdef _DEBUG
          printf( "%s\n",infoLog );
        #endif
        free( infoLog );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Generate and print log related with the program. 
// 
///////////////////////////////////////////////////////////////////////////////

void printProgramInfoLog( GLuint obj )
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

  	glGetProgramiv( obj, GL_INFO_LOG_LENGTH,&infologLength );

    if( infologLength > 0 )
    {
        infoLog = ( char * )malloc( infologLength );
        glGetProgramInfoLog( obj, infologLength, &charsWritten, infoLog );
        #ifdef _DEBUG
		    printf( "%s\n",infoLog );
        #endif
        free( infoLog );
    }
}

#endif // __SHADER_DEBUG_H__
