
#ifndef __MSG_CORE_VIEWER_H__
#define __MSG_CORE_VIEWER_H__

#include "Export.h"
#include "Core/NodeVisitor.h"

namespace Mirage
{
  namespace Core
  {
    class MSG_EXPORT Viewer : public Referenced
    {
      public:

        Viewer();       
        
        virtual void              init();

        virtual Node*             sceneData();
        virtual void              sceneData( Node* node );

        // @Todo: Add functions to get and set visitors. 

        virtual void              update();

        virtual void              draw();


      protected: 

        ~Viewer();  


      protected: 

        SmartPtr< Group >         _root;        

        SmartPtr< NodeVisitor >   _updateNodeVisitor;
        SmartPtr< NodeVisitor >   _drawNodeVisitor;
    };
  }
}


#endif // __MSG_CORE_VIEWER_H__
