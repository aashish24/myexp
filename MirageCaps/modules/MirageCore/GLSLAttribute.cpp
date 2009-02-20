
#include "MirageCore/GLSLAttribute.h"

namespace Mirage
{
  namespace MirageCore
  {
    GLSLAttribute::GLSLAttribute() :     
      StateAttribute()
    {
      try
      {
        _glslProgram = new GLSLProgram();
      }
      catch( std::bad_alloc )
      {
        // ERROR.
        _glslProgram = 0x00;
      }
    }


    GLSLAttribute::~GLSLAttribute()
    { 
    }

        
    void GLSLAttribute::init()
    {
    }

    
    void GLSLAttribute::conextInit()
    {
      this->set();
    }


    void GLSLAttribute::activate( Node* node )
    {
      std::vector< SmartPtr< Uniform > >::iterator itr; 

      // Call GL function to set uniform value. 
      for( itr = _uniforms.begin(); itr != _uniforms.end(); ++itr )
      {       
       ( *itr )->callGL();
      }
    }

   
    void GLSLAttribute::deActivate( Node* node )
    {
    }


    void GLSLAttribute::addShader( MirageCore::GLSLShader* shader )
    {
    }


    void GLSLAttribute::addUniform( Uniform* uniform )
    {
      if( !uniform )
      {
        return;
      }

      _uniforms.push_back( uniform );
    }



    void GLSLAttribute::set()
    {      
      if( !_glslProgram.valid() )
      {
        // WARNING. 
        return;
      }

      if ( _shaders.find( IShader::VERTEX_SHADER ) == _shaders.end() || 
           _shaders.find( IShader::FRAGMENT_SHADER ) == _shaders.end()  )
      {
        // WARNING. 
        return;
      }

      
      try
      {
        _shaders[IShader::VERTEX_SHADER]->contextInit();
        _shaders[IShader::FRAGMENT_SHADER]->contextInit();

        _glslProgram->attach( _shaders[IShader::VERTEX_SHADER].get() );
        _glslProgram->attach( _shaders[IShader::FRAGMENT_SHADER].get() );
        
        _glslProgram->link();

        
        std::vector< SmartPtr< Uniform > >::iterator itr; 

        for( itr = _uniforms.begin(); itr != _uniforms.end(); ++itr )
        {
          ( *itr )->getAndSetLocation( _glslProgram.get() );        
          //( *itr )->callGL();
        }
      }
      catch( std::exception& e )
      {
        // ERROR. 
      }
      catch( ... )
      {
        // ERROR. 
      }

      this->dirty( false );
    }
  }
}

