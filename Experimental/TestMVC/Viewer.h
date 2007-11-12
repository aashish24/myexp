
#ifndef __OGE_OGE_OSG_OGE_OSG_VIEWER_VIWER_H__
#define __OGE_OGE_OSG_OGE_OSG_VIEWER_VIWER_H__

#include "IFindNode.h"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgViewer
    {
      class Viewer : public Oge::OgeBase::OgeInterfaces::IFindNode< osg::Node >
      {
        public: 
          osg::Node* findNode( const std::string& id );

      };
    }
  }
}

osg::Node* Oge::OgeOsg::OsgViewer::Viewer::findNode( const std::string& id )
{
  return 0x00;
}

#endif // __OGE_OGE_OSG_OGE_OSG_VIEWER_VIWER_H__
