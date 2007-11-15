
#ifndef __OSG_QT_GL_WIDGET_H__
#define __OSG_QT_GL_WIDGET_H__

#if USE_QT4
    #include <QtCore/QString>
    #include <QtCore/QTimer>
    #include <QtGui/QKeyEvent>
    #include <QtGui/QApplication>
    #include <QtOpenGL/QGLWidget>
    
    using Qt::WindowFlags;
#else
    class QWidget;   
    #define WindowFlags WFlags
#endif

#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

namespace Oge
{ 
  namespace OgeOsg
  {
    namespace OsgQt
    {
      class AdapterWidget : public QGLWidget
      {
          public:

              AdapterWidget( QWidget * parent = 0, 
                             const char * name = 0, 
                             const QGLWidget * shareWidget = 0, 
                             WindowFlags f = 0 );

              virtual ~AdapterWidget() {}

              osgViewer::GraphicsWindow*                        getGraphicsWindow() { return _gw.get(); }
              const osgViewer::GraphicsWindow*                  getGraphicsWindow() const { return _gw.get(); }

          protected:

              void                                              init();

              virtual void                                      resizeGL( int width, int height );
              virtual void                                      keyPressEvent( QKeyEvent* event );
              virtual void                                      keyReleaseEvent( QKeyEvent* event );
              virtual void                                      mousePressEvent( QMouseEvent* event );
              virtual void                                      mouseReleaseEvent( QMouseEvent* event );
              virtual void                                      mouseMoveEvent( QMouseEvent* event );

              osg::ref_ptr< osgViewer::GraphicsWindowEmbedded > _gw;
      };
    }
  }
}

#endif // __OSG_QT_GL_WIDGET_H__
