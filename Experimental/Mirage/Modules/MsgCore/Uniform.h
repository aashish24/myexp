
#ifndef __MSG_CORE_UNIFORM_SAMPLER_2D_H__
#define __MSG_CORE_UNIFORM_SAMPLER_2D_H__

#include "Export.h"

#include "MsgCore/Object.h"
#include "MsgCore/IUniform.h"

#include "GL/glew.h"
#include "GL/gl.h"

#include <typeinfo>

namespace Msg
{
  namespace MsgCore
  {
    // Forward declaration. 
    class GLSLProgram;

    struct MSG_EXPORT Uniform : public IUniform, public MsgCore::Object
    {
      Uniform( const std::string& name = std::string( "" ), const int& location = -1 );

      virtual std::string name() const;
      virtual void        name( const std::string& name );

      virtual int         location() const;
      virtual void        location( const int& location );

      virtual void        getAndSetLocation( GLSLProgram* glslProgram );

      protected: 

        virtual ~Uniform();

      
      protected: 

        std::string       _name;

        int               _location;
    };

    
    template< typename T > 
    struct GLCall;


    template<>
    struct GLCall< int > 
    {
      GLCall( const int& location, const int& value )
      {
        glUniform1i( location, value );
      }


      GLCall( const int& location, const int& value1, const int& value2 )
      {
        glUniform2i( location, value1, value2 );
      }
    };

    
    template<>
    struct GLCall< bool > 
    {
      GLCall( const int& location, const int& value )
      {
        glUniform1i( location, value );
      }


      GLCall( const int& location, const int& value1, const int& value2 )
      {
        glUniform2i( location, value1, value2 );
      }
    };


    template<>
    struct GLCall< float > 
    {
      GLCall( const int& location, const float& value )
      {
        glUniform1f( location, value );        
      }


      GLCall( const int& location, const float& value1, const float& value2 )
      {
        glUniform2f( location, value1, value2 );
      }
    };


    template< typename DATA_TYPE >
    class MSG_EXPORT Uniform1 : public MsgCore::Uniform
    {
      public: 

        Uniform1() : 
          Uniform (), 
          _value  ( 0 )
        {
        }


        Uniform1( const std::string& name, const int& location, const DATA_TYPE& value = 0 ) :
          Uniform( name, location ), 
          _value ( value )
        {
        }
       

        void get( DATA_TYPE& value )
        {
          value = _value;
        }
        

        void set( const DATA_TYPE& value ) 
        {
          _value = value;
        }


        void callGL() const
        {
          GLCall< DATA_TYPE > call( location(), _value );
        }


      protected:

        ~Uniform1() 
        {
        }


      private:        

        DATA_TYPE             _value;
    };

    
    template< typename DATA_TYPE >
    class MSG_EXPORT Uniform2 : public MsgCore::Uniform
    {
      public: 

        Uniform2() : 
          Uniform (), 
          _value1 ( 0 ), 
          _value2 ( 0 ), 
        {
        }


        Uniform2( const std::string& name, const int& location, const DATA_TYPE& value1 = 0, const DATA_TYPE& value2 = 0 ) :
          Uniform( name, location ), 
          _value1 ( value1 )
          _value2 ( value2 )
        {
        }
       

        void get( DATA_TYPE& value1, DATA_TYPE& value2 )
        {
          value1 = _value1;
          value2 = _value2;
        }
        

        void set( const DATA_TYPE& value1, const DATA_TYPE& value2 ) 
        {
          _value1 = value1;
          _value2 = value2;
        }


        void callGL() const
        {
          GLCall< DATA_TYPE > call( location(), _value1, _value2 );
        }


      protected:

        ~Uniform2() 
        {
        }


      private:        

        DATA_TYPE             _value1;
        DATA_TYPE             _value2;
    };

    
    typedef Uniform1< int >   Uniform1i;
    typedef Uniform1< bool >  Uniform1b;
    typedef Uniform1< float > Uniform1f;

    typedef Uniform2< int >   Uniform2i;
    typedef Uniform2< bool >  Uniform2b;
    typedef Uniform2< float > Uniform2f;
  }
}

#endif // __MSG_CORE_UNIFORM_SAMPLER_2D_H__
