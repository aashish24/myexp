
#include "MsgCore/Viewer.h"

namespace Msg
{
  namespace MsgCore
  {
    Viewer::Viewer()  
    {
      try
      {
        _root = new Group();

        _updateNodeVisitor  = new NodeVisitor( NodeVisitor::UPDATE ); 
        _drawNodeVisitor    = new NodeVisitor( NodeVisitor::DRAW );
      }
      catch( std::bad_alloc& e ) 
      {
        std::cerr << " Exception " << e.what() << " raised: " << std::endl; 
      }
    }


    Viewer::~Viewer()
    {
    }


    void  Viewer::init()
    {
    }


    Node* Viewer::getSceneData()
    {
      return _root->child( 0 );
    }


    void  Viewer::setSceneData( Node* node )
    {
      _root->addChild( node );
    }

    
    void  Viewer::update()
    {
      _root->accept( *_updateNodeVisitor.get() );
    }


    void  Viewer::draw()
    {
       _root->accept( *_drawNodeVisitor.get() );
    }
  }
}

