
#ifndef __MSG_CORE_DRAWABLE_H__
#define __MSG_CORE_DRAWABLE_H__

#include "Export.h"
#include "MsgCore/Object.h"
#include "MsgCore/StateSet.h"

#ifdef WIN32
	#include <windows.h>
#endif 

#include "GL/glew.h"
#include "GL/gl.h"

#include "MsgCore/Node.h"

#include <iostream>
#include <vector>

namespace Msg
{
	namespace MsgCore
	{
		class Geode;			

		class MSG_EXPORT Drawable : public Node
		{
			public:
				typedef std::vector< Geode* > Parents; 
				typedef std::vector< GLuint > GLObjectList;

				Drawable();
				Drawable( const Drawable& drawable );

        //void                          addParent( Geode* parent );
        //const Parents                 getParents() const ;
        //Parents                       getParents();
        //unsigned int                  getNumParents();

        //const StateSet*               getStateSet() const;
        //StateSet*                     getStateSet();
          
			  void                          setUseDisplayList( bool flag );
        bool                          getUseDisplayList( unsigned int contextID );
        bool                          getUseDisplayList();
        GLuint&                       getDisplayList( unsigned int contextID );

        void                          draw();
				virtual void                  drawImplementation() const;
				

			protected:

        virtual ~Drawable()
        {
          // Do nothing. 
        }


			protected:

        bool					                _useDisplayList;

				//Parents					              _parents;

				//SmartPtr< StateSet >	        _stateSet;

				mutable GLObjectList	        _glObjectList;
		};

    
   /* inline void Drawable::addParent( Geode* parent )
		{
			_parents.push_back( parent );
		}


    inline const Drawable::Parents Drawable::getParents() const
		{
			return _parents;
		}


    inline Drawable::Parents Drawable::getParents()
		{
			return _parents;
		}


    inline unsigned int Drawable::getNumParents()
		{
			return ( unsigned int )_parents.size();
		}
		

		inline const StateSet* Drawable::getStateSet() const
		{
			return _stateSet.get();
		}

		
    inline StateSet* Drawable::getStateSet() 
		{
			return _stateSet.get();
		}*/


    inline void Drawable::setUseDisplayList( bool flag )
		{
			_useDisplayList = flag;
		}


		inline bool Drawable::getUseDisplayList()
		{
			return _useDisplayList;
		}


		inline GLuint& Drawable::getDisplayList( unsigned int contextID )
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
			  std::cout << "[draw] New display list generated" << std::endl;
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
