
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

    class OSGTOOLS_EXPORT OsgFind
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

        static osg::Node* 	              findNodeByName    ( osg::Node*  node, const std::string& id, Dir dir = DOWN );            

        static Nodes     	                findAllNodesByName( osg::Node*  node, const std::string& id, Dir dir = DOWN ); 
    };     
  }
}

#endif // __OSGTOOLS_SG_OSGFIND_H__
