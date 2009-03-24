
#ifndef __MSG_CORE_UNIFORM_SAMPLER_2D_H__
#define __MSG_CORE_UNIFORM_SAMPLER_2D_H__

#include "Export.h"

#include "MirageCore/Object.h"
#include "MirageCore/IUniform.h"

#include "GL/glew.h"
#include "GL/gl.h"

#include <typeinfo>

namespace Mirage
{
  namespace MirageCore
  {
    // Forward declaration. 
    class GLSLProgram;

    struct MSG_EXPORT Uniform : public IUniform, public MirageCore::Object
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


    template< typename DataTypeT >
    class MSG_EXPORT Uniform1 : public MirageCore::Uniform
    {
      public: 

        Uniform1() : 
          Uniform (), 
          _value  ( 0 )
        {
        }


        Uniform1( const std::string& name, const int& location, const DataTypeT& value = 0 ) :
          Uniform( name, location ), 
          _value ( value )
        {
        }
       

        void get( DataTypeT& value )
        {
          value = _value;
        }
        

        void set( const DataTypeT& value ) 
        {
          _value = value;
        }


        void callGL() const
        {
          GLCall< DataTypeT > call( location(), _value );
        }


      protected:

        ~Uniform1() 
        {
        }


      private:        

        DataTypeT             _value;
    };

    
    template< typename DataTypeT >
    class MSG_EXPORT Uniform2 : public MirageCore::Uniform
    {
      public: 

        Uniform2() : 
          Uniform (), 
          _value1 ( 0 ), 
          _value2 ( 0 ), 
        {
        }


        Uniform2( const std::string& name, const int& location, const DataTypeT& value1 = 0, const DataTypeT& value2 = 0 ) :
          Uniform( name, location ), 
          _value1 ( value1 )
          _value2 ( value2 )
        {
        }
       

        void get( DataTypeT& value1, DataTypeT& value2 )
        {
          value1 = _value1;
          value2 = _value2;
        }
        

        void set( const DataTypeT& value1, const DataTypeT& value2 ) 
        {
          _value1 = value1;
          _value2 = value2;
        }


        void callGL() const
        {
          GLCall< DataTypeT > call( location(), _value1, _value2 );
        }


      protected:

        ~Uniform2() 
        {
        }


      private:        

        DataTypeT             _value1;
        DataTypeT             _value2;
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
