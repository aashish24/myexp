
#ifndef __MSG_CORE_DRAWABLE_H__
#define __MSG_CORE_DRAWABLE_H__

#include "Export.h"
#include "MsgCore/Object.h"
#include "MsgCore/StateSet.h"

#ifdef WIN32
	#include <windows.h>
#endif 

#include "GL/glew.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include "GL/gl.h"
#endif

#include "MsgCore/Node.h"

#include <iostream>
#include <vector>

namespace Msg
{
	namespace MsgCore
	{
		class Geode;			

    class MSG_EXPORT Drawable : public Msg::MsgCore::Node
		{
			public:

				typedef std::vector< Geode* > Parents; 
				typedef std::vector< GLuint > GLObjectList;

				Drawable();

				Drawable( const Drawable& drawable );
          
			  void                          useDisplayList( bool flag );
        
        bool                          useDisplayList( unsigned int contextID );
        
        bool                          useDisplayList();
        
        GLuint&                       displayList( unsigned int contextID );

        void                          draw();
				
        virtual void                  drawImplementation();
				

			protected:

        virtual ~Drawable()
        {        
        }


			protected:

        bool					                _useDisplayList;				

				mutable GLObjectList	        _glObjectList;
		};    
  

    inline void Drawable::useDisplayList( bool flag )
		{
			_useDisplayList = flag;
		}


		inline bool Drawable::useDisplayList()
		{
			return _useDisplayList;
		}


		inline GLuint& Drawable::displayList( unsigned int contextID )
		{
			// Only once display list is associated as of now. 
			return _glObjectList[0];
		}
     

    inline void Drawable::draw()
	  { 
      // Should we compile this into display list? 
      this->activateStateSet();

		  // If this is not the first time. 
		  if( !_glObjectList.empty() )
		  {						
			  for( size_t i=0; i < _glObjectList.size(); ++i )
			  {
				  glCallList( _glObjectList[i] );
			  }
		  }
		  else
		  {
			  GLuint globj;			  
			  globj = glGenLists( 1 );
			  _glObjectList.clear();
			  _glObjectList.push_back( globj );
			  glNewList( globj, GL_COMPILE );
				  drawImplementation();
			  glEndList();
        glCallList( globj );
		  }
      
      this->deActivateStateSet();

		  return;
	  }   
	}
}

#endif // __DRAWABLE_H__
