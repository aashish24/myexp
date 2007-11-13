
// This is QT-OSG fusion exmple. 

#include "osgDB/ReadFile"

#include "OsgModel.h"
#include "Viewer.h"

#include "QtGui"
#include "QtOpenGL"
#include "QApplication"
#include "QWidget"
#include "QGLWidget"


typedef Oge::OgeOsg::OsgViewer::Viewer Viewer;

class GLWidget : public QGLWidget
{
  Q_OBJECT

  public:    
    
  
    GLWidget(QWidget *parent = 0) : QGLWidget( parent )
    {
    }

   ~GLWidget()
    {
    }

    void setViewer( Viewer* viewer )
    {
      _viewer = viewer;
    }

  protected:

    void initializeGL() 
    {
      _viewer->contextInit();
    }

    void paintGL()
    {
      _viewer->run();
    }

  protected: 
    Viewer* _viewer;
    
};

class Window : public QWidget 
{
  Q_OBJECT

  public: 
    Window()
    {
      _glWidget = new GLWidget;

      QHBoxLayout* layout = new QHBoxLayout();
      layout->addWidget( _glWidget );
      setLayout( layout );
    }

  protected: 
    GLWidget* _glWidget;
};

int main( int argc, char** argv )
{
  QApplication app( argc, argv );
  
  osg::Node* node = osgDB::readNodeFile( "cow.osg" );
  
  Viewer viewer( Oge::OgeOsg::OsgViewer::Viewer::EMBEDDED );

  viewer.setModelData( node );
  
  viewer.setEmbeddedDisplaySize( 0, 0, 200, 200 );


  Window window;

  window.show();

  return app.exec();
}

