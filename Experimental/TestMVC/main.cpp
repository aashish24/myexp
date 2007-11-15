
// This is QT-OSG fusion exmple. 

#include <iostream>

#include "osgDB/ReadFile"

#include "Oge/OgeOsg/OsgCore/OsgModel.h"

#include "Oge/OgeOsg/OsgQt/ViewerQt.h"

#if USE_QT4
    #include "QtCore/QString"
    #include "QtCore/QTimer"
    #include "QtGui/QKeyEvent"
    #include "QtGui/QApplication"
    #include "QtOpenGL/QGLWidget"
    
    using Qt::WindowFlags;
#else
    class QWidget;
    #include "qtimer.h"
    #include "qgl.h"
    #include "qapplication.h"

    #define WindowFlags WFlags
#endif


int main( int argc, char **argv )
{
  typedef Oge::OgeOsg::OsgQt::ViewerQt ViewerQt;
    
  QApplication a( argc, argv );
  
  if (argc<2)
  {
      std::cout << argv[0] <<": requires filename argument." << std::endl;
      return 1;
  }

  osg::ArgumentParser arguments(&argc, argv);

  // load the scene.
  osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFiles(arguments);
  if (!loadedModel)
  {
      std::cout << argv[0] <<": No data loaded." << std::endl;
      return 1;
  }

  ViewerQt* viewerWindow = new ViewerQt;

  viewerWindow->setCameraManipulator(new osgGA::TrackballManipulator);
  viewerWindow->setModelData( loadedModel.get() );

  viewerWindow->show();   
  
  a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
 
  return a.exec();
}

