
#include "Oge/OgeOsg/OsgQt/AdapterWidget.h"

namespace Oge
{ 
  namespace OgeOsg
  {
    namespace OsgQt
    {
      AdapterWidget::AdapterWidget( QWidget * parent, 
                                    const char * name, 
                                    const QGLWidget * shareWidget, 
                                    WindowFlags f ):
      #if USE_QT4
          QGLWidget( parent, shareWidget, f )
      #else
          QGLWidget( parent, name, shareWidget, f )
      #endif // USE_QT4
      {
          _gw = new osgViewer::GraphicsWindowEmbedded( 0, 0, width(), height() );
      }


      void AdapterWidget::resizeGL( int width, int height )
      {
          _gw->getEventQueue()->windowResize( 0, 0, width, height );
          _gw->resized( 0,0,width,height );
      }


      void AdapterWidget::keyPressEvent( QKeyEvent* event )
      {
        #if USE_QT4
          _gw->getEventQueue()->keyPress( ( osgGA::GUIEventAdapter::KeySymbol ) *( event->text().toAscii().data() ) );
        #else
          _gw->getEventQueue()->keyPress( (osgGA::GUIEventAdapter::KeySymbol) event->ascii() );
        #endif
      }


      void AdapterWidget::keyReleaseEvent( QKeyEvent* event )
      {
        #if USE_QT4
          _gw->getEventQueue()->keyRelease( ( osgGA::GUIEventAdapter::KeySymbol ) *( event->text().toAscii().data() ) );
        #else
          _gw->getEventQueue()->keyRelease( (osgGA::GUIEventAdapter::KeySymbol) event->ascii() );
        #endif
      }


      void AdapterWidget::mousePressEvent( QMouseEvent* event )
      {
          int button = 0;
          switch( event->button() )
          {
              case( Qt::LeftButton ):   button = 1; break;
              case( Qt::MidButton ):    button = 2; break;
              case( Qt::RightButton ):  button = 3; break;
              case( Qt::NoButton ):     button = 0; break;
              default:                  button = 0; break;
          }
          _gw->getEventQueue()->mouseButtonPress( event->x(), event->y(), button );
      }


      void AdapterWidget::mouseReleaseEvent( QMouseEvent* event )
      {
          int button = 0;
          switch( event->button() )
          {
              case(Qt::LeftButton):   button = 1; break;
              case(Qt::MidButton):    button = 2; break;
              case(Qt::RightButton):  button = 3; break;
              case(Qt::NoButton):     button = 0; break;
              default:                button = 0; break;
          }
          _gw->getEventQueue()->mouseButtonRelease( event->x(), event->y(), button );
      }

      void AdapterWidget::mouseMoveEvent( QMouseEvent* event )
      {
          _gw->getEventQueue()->mouseMotion( event->x(), event->y() );
      }
    }
  }
}
