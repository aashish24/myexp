
#ifndef __OSG_QT_VIEWER_QT_H__
#define __OSG_QT_VIEWER_QT_H__

#include "Oge/Export.h"

#include "Oge/OgeOsg/OsgViewer/Viewer.h"
#include "Oge/OgeOsg/OsgQt/AdapterWidget.h"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgQt
    {
      namespace ov = Oge::OgeOsg::OsgViewer;
      namespace oa = Oge::OgeOsg::OsgQt;

      class OGE_EXPORT ViewerQt : public ov::Viewer, public oa::AdapterWidget
      {
          public:
              ViewerQt( QWidget * parent = 0, 
                        const char * name = 0, 
                        const QGLWidget * shareWidget = 0, 
                        WindowFlags f = 0,
                        double fov = 30.0, 
                        double zNear = 1.0, 
                        double zFar  = 1000.0 ):
                Viewer          ( Viewer::EMBEDDED ), 
                AdapterWidget ( parent, name, shareWidget, f )
              {
                  getCamera()->setViewport( new osg::Viewport( 0,0,width(), height() ) );                  
                  
                  getCamera()->setProjectionMatrixAsPerspective( 
                    fov,
                    static_cast< double >( width() )/static_cast< double >( height() ), 
                    zNear, 
                    zFar );

                  getCamera()->setGraphicsContext( getGraphicsWindow() );

                  setThreadingModel( osgViewer::Viewer::SingleThreaded );

                  connect( &_timer, SIGNAL( timeout() ), this, SLOT( updateGL() ) );
                  _timer.start( 10 );
              }

              virtual void paintGL()
              {
                  run();
              }
          
          protected:

              QTimer _timer;
      };
    } // namespace Oge
  } // namespace OgeOsg
} // namespace OsgQt

#endif // __OSG_QT_VIEWER_QT_H__
