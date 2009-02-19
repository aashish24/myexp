
#ifndef __MSG_CORE_I_VIEWER_H__
#define __MSG_CORE_I_VIEWER_H__

namespace Mirage
{
  namespace MirageCore
  {
    class IViewer 
    {
      public:
        
        virtual void  init()                  = 0;

        virtual Node* sceneData()             = 0; 
        virtual void  sceneData( Node* node ) = 0;

        virtual void  update()                = 0;

        virtual void  draw()                  = 0;
    };
  }
}


#endif // __MSG_CORE_I_VIEWER_H__
