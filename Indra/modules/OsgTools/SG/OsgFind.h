
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Find a node given a identifier in a scenegraph.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OSGTOOLS_SG_OSGFIND_H__
#define __OSGTOOLS_SG_OSGFIND_H__

#include <vector>

#include "osg/Node"
#include "osg/Group"
#include "osg/Referenced"

#include "OsgTools/Core/Export.h"

namespace OsgTools
{
  namespace SG
  {

    /////////////////////////////////////////////////////////////////////////
    //
    // Typedefs.
    //
    /////////////////////////////////////////////////////////////////////////
        
    typedef std::vector< osg::Node* >     Nodes;

    class OSGTOOLS_EXPORT OsgFind : public osg::Referenced
    {
      public:

        /////////////////////////////////////////////////////////////////////////
        //
        // Traversal direction. 
        //
        /////////////////////////////////////////////////////////////////////////
        
        enum Dir
        {
          UP = 0, 
          DOWN
        };

        static osg::Node* findNodeByName    ( osg::Node*  node, const std::string& id, Dir dir = DOWN );            
        static Nodes     	findAllNodesByName( osg::Node*  node, const std::string& id, Dir dir = DOWN ); 

      protected:
        
        OsgFind();
        
        // We cannot leave it undefined as compiler creates scalar deleting 
        // destructor as shown below and leaving it undefined will cause a link error.
        //
        // It's the name that's reported for a helper function that VC writes for every
        // class with a destructor. The "scalar deleting destructor" for class A is
        // roughly equivalent to:
        //
        // void scalar_deleting_destructor(A* pa)
        // {
        //    pa->~A();
        //    A::operator delete(pa);
        // }
        //
        // There's a sister function that's also generated, which is called the 'vector
        // deleting destructor'. It looks roughly like:
        //
        // void vector_deleting_destructor(A* pa, size_t count)
        // {
        //    for (size_t i = 0; i < count; ++i)
        //    pa[i].~A();
        //    A::operator delete[](pa);
        // }
        //
        // When you write
        //
        // A* pa;
        // ...
        //
        // delete pa;
        //
        // The compiler generates a call to the "scalar deleting destructor" for A. An
        // analogous case applies to deleting an array.

        ~OsgFind()
        {
        }
    };     
  }
}

#endif // __OSGTOOLS_SG_OSGFIND_H__
