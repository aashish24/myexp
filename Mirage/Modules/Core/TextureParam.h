
#ifndef __MIRAGE_CORE_TEXTURE_PARAM_H__
#define __MIRAGE_CORE_TEXTURE_PARAM_H__

#include "Export.h"

#include "Core/StateAttribute.h" 
#include "Core/Object.h"

#include "GL/glew.h"

namespace Mirage
{
	namespace Core
	{
    class MSG_EXPORT TextureParam : public Object
		{
			public:
				
        TextureParam() : Object(), 
          _wrapS    ( GL_REPEAT ), 
          _wrapT    ( GL_REPEAT ), 
          _wrapR    ( GL_REPEAT ), 
          _magFilter( GL_LINEAR ), 
          _minFilter( GL_LINEAR )        
        {
        }		        


        const unsigned& getWrapS() const
        {
          return _wrapS; 
        }


        void setWrapS(const unsigned& val) 
        {
          _wrapS = val;   
        }


        const unsigned& getWrapT() const
        {
          return _wrapT; 
        }


        void setWrapT(const unsigned& val)
        {
          _wrapT = val;
        }


        const unsigned& getWrapR() const
        {
          return _wrapR; 
        }

        void setWrapR(const unsigned& val)
        {
          _wrapR = val;
        }


        const unsigned& getMagFilter() const
        {
          return _magFilter;
        }

        void setMagFilter(const unsigned& val)
        {
          _magFilter = val; 
        }


        const unsigned& getMinFilter() const
        {
          return _minFilter;
        }
        
        void setMinFilter(const unsigned& val)
        {
          _minFilter = val;
        }


      protected: 
        
        ~TextureParam()
        {
        }


      public:  
        
        unsigned _wrapS; 
        unsigned _wrapT; 
        unsigned _wrapR; 

        unsigned _minFilter; 
        unsigned _magFilter;
    };
  }
}

#endif  __MIRAGE_CORE_TEXTURE_PARAM_H__


