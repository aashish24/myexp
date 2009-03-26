
#include "Core/Viewer.h"

#include "GL/glew.h"
#include "GL/gl.h"

namespace Mirage
{
  namespace Core
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


    Node* Viewer::sceneData()
    {
      return _root->child( 0 );
    }


    void  Viewer::sceneData( Node* node )
    {
      _root->addChild( node );
    }

    
    void  Viewer::update()
    {
      _root->accept( *_updateNodeVisitor.get() );
    }


    void  Viewer::draw()
    {
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
       _root->accept( *_drawNodeVisitor.get() );
    }
  }
}

