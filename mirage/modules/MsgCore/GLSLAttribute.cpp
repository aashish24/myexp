
#include "MsgCore/GLSLAttribute.h"

namespace Msg
{
  namespace MsgCore
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


    // Return id of the attribute. 
    std::string GLSLAttribute::id() const
    {
      return std::string( "GLSLAttribute" );
    }

        
    void GLSLAttribute::init()
    {
    }

    
    void GLSLAttribute::contextInit()
    {
      this->set();
    }


    void GLSLAttribute::activate( Node* node )
    {
      if( this->dirty() )
      {
        this->contextInit();    
      }

      std::vector< SmartPtr< Uniform > >::iterator itr; 

      // Call GL function to set uniform value. 
      for( itr = _uniforms.begin(); itr != _uniforms.end(); ++itr )
      {       
       ( *itr )->callGL();
      }

      glUseProgram( _glslProgram->glObject() );
    }

   
    void GLSLAttribute::deActivate( Node* node )
    {
      glUseProgram( _glslProgram->glObject() );
    }


    void GLSLAttribute::addShader( MsgCore::GLSLShader* shader )
    {
      _shaders[shader->getType()] = shader;
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

      if ( _shaders.find( IShader::VERTEX ) == _shaders.end() || 
           _shaders.find( IShader::FRAGMENT ) == _shaders.end()  )
      {
        // WARNING. 
        return;
      }

      
      try
      {
        _glslProgram->contextInit();

        _shaders[IShader::VERTEX]->contextInit();
        _shaders[IShader::FRAGMENT]->contextInit();

        _glslProgram->attach( _shaders[IShader::VERTEX].get() );
        _glslProgram->attach( _shaders[IShader::FRAGMENT].get() );
        
        _glslProgram->link();

        
        std::vector< SmartPtr< Uniform > >::iterator itr; 

        for( itr = _uniforms.begin(); itr != _uniforms.end(); ++itr )
        {
          ( *itr )->getAndSetLocation( _glslProgram.get() );                  
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

