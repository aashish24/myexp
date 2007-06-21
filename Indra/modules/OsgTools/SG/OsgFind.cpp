
#include "OsgTools/SG/OsgFind.h"

#include <iostream>

using namespace OsgTools::SG;

/////////////////////////////////////////////////////////////////////////
//
// Search for a node starting at the point where curNode is 
// and return a osg::Node/ if node with id id 
// exists in the tree. 
//
/////////////////////////////////////////////////////////////////////////

inline osg::Node* OsgFind::findNodeByName( osg::Node* node, const std::string& id, Dir dir )
{
  osg::ref_ptr< osg::Group > currGroup;
  osg::ref_ptr< osg::Node >  foundNode;

  // Check to see if we have a valid (non-NULL) node. 
  // If we do have a null node, return NULL.
  if ( !node )
  {
    return 0x00;
  }

  // We have a valid node, check to see if this is the node we 
  // are looking for. If so, return the current node.
  if ( node->getName() == id )
  {
    return node;
  }

  // We have a valid node, but not the one we are looking for.
  // Check to see if it has children (non-leaf node). If the node
  // has children, check each of the child nodes by recursive call.
  // If one of the recursive calls returns a non-null value we have
  // found the correct node, so return this node.
  // If we check all of the children and have not found the node,
  // return NULL

  switch( dir )
  {
    case DOWN:
    {
      currGroup = node->asGroup();
      if( !currGroup.valid() ) return 0x00;
      
      for( unsigned int i = 0 ; i < currGroup->getNumChildren(); i++ )
      {       
        foundNode = findNodeByName( currGroup->getChild(i), id, DOWN );
        if ( foundNode.get() )
        {
          // found a match!
          return foundNode.get(); 
        }
      }

      return 0x00;
      break;
    }
    case UP:
    {
      for( unsigned int i = 0; i < node->getNumParents(); i++ )
      {       
        if( node->getNumParents() <= 0 ) return 0x00;
        currGroup = node->getParent(i);
        foundNode = findNodeByName( currGroup.get(), id, UP );
        if ( foundNode.get() )
        {
          // found a match!
          return foundNode.get(); 
        }
      }
      return 0x00;
      break;    
    }
    default: 
    {
      std::cerr << "Error 2966768110: Traversal direction " << dir << " not handled: " << std::endl;
      return 0x00;
      break;
    }
  };    
}


/////////////////////////////////////////////////////////////////////////
//
// Search for a node or nodes starting at the point where curNode is 
// and return a vector of osg::Node* if node or nodes with id 
// id exists in the tree. 
//
/////////////////////////////////////////////////////////////////////////

inline Nodes OsgFind::findAllNodesByName( osg::Node*  node, const std::string& id, Dir dir )
{
  Nodes                       nodes;
  Nodes                       children;

  osg::ref_ptr< osg::Group >  currGroup;
  osg::ref_ptr< osg::Node >   foundNode;

  nodes.clear();
  children.clear();

  // Check to see if we have a valid (non-NULL) node. 
  // If we do have a null node, return NULL.
  if ( !node )
  {
    return nodes;
  }

  // We have a valid node, check to see if this is the node we 
  // are looking for. If so, return the current node.
  if ( node->getName() == id )
  {
    nodes.push_back( node );
  }

  // We have a valid node, but not the one we are looking for.
  // Check to see if it has children (non-leaf node). If the node
  // has children, check each of the child nodes by recursive call.
  // If one of the recursive calls returns a non-null value we have
  // found the correct node, so return this node.
  // If we check all of the children and have not found the node,
  // return NULL
  currGroup = node->asGroup(); // returns NULL if not a group.
  if( currGroup.get() ) 
  {
    for( unsigned int i = 0 ; i < currGroup->getNumChildren(); ++i )
    {     
     children = findAllNodesByName( currGroup->getChild( i ), id );

     if (children.size() > 0 )
     {
       unsigned int nChild = 0;
       for( nChild = 0; nChild < children.size(); ++nChild )
       {
        nodes.push_back( children.at(nChild) );
       }
     }
    }
   }

  return nodes;
}  