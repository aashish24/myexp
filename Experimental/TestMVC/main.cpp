
// This is QT-OSG fusion exmple. 

#include <iostream>

#include "osgDB/ReadFile"

#include "Oge/OgeOsg/OsgCore/OsgModel.h"

#include "Oge/OgeOsg/OsgViewer/Viewer.h"

#if USE_QT4

    #include <QtCore/QString>
    #include <QtCore/QTimer>
    #include <QtGui/QKeyEvent>
    #include <QtGui/QApplication>
    #include <QtOpenGL/QGLWidget>
    
    using Qt::WindowFlags;

#else

    class QWidget;
    #include <qtimer.h>
    #include <qgl.h>
    #include <qapplication.h>

    #define WindowFlags WFlags

#endif

#include "Oge/OgeOsg/OsgQt/AdapterWidget.h"

typedef Oge::OgeOsg::OsgViewer::Viewer Viewer;
typedef Oge::OgeOsg::OsgQt::AdapterWidget AdapterWidget;

class ViewerQT : public Viewer, public AdapterWidget
{
    public:

        ViewerQT( QWidget * parent = 0, const char * name = 0, const QGLWidget * shareWidget = 0, WindowFlags f = 0 ):
            AdapterWidget( parent, name, shareWidget, f )
        {
            getCamera()->setViewport( new osg::Viewport( 0,0,width(), height() ) );
            getCamera()->setProjectionMatrixAsPerspective( 
              30.0f, 
              static_cast< double >( width() )/static_cast< double >( height() ), 
              1.0f, 10000.0f );

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

class CompositeViewerQT : public osgViewer::CompositeViewer, public AdapterWidget
{
    public:

        CompositeViewerQT( QWidget * parent = 0, const char * name = 0, const QGLWidget * shareWidget = 0, WindowFlags f = 0 ):
            AdapterWidget( parent, name, shareWidget, f )
        {
            setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );

            connect( &_timer, SIGNAL(timeout()), this, SLOT(updateGL()) );
            _timer.start( 10 );
        }

        virtual void paintGL()
        {
            frame();
        }
    
    protected:

        QTimer _timer;
};

int main( int argc, char **argv )
{
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
    
    
    if (arguments.read("--CompositeViewer"))
    {
        CompositeViewerQT* viewerWindow = new CompositeViewerQT;

        unsigned int width = viewerWindow->width();
        unsigned int height = viewerWindow->height();
        
        {
            osgViewer::View* view1 = new osgViewer::View;
            view1->getCamera()->setGraphicsContext(viewerWindow->getGraphicsWindow());
            view1->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width)/static_cast<double>(height/2), 1.0, 1000.0);
            view1->getCamera()->setViewport(new osg::Viewport(0,0,width,height/2));
            view1->setCameraManipulator(new osgGA::TrackballManipulator);
            view1->setSceneData(loadedModel.get());
            
            viewerWindow->addView(view1);
        }
        
        {
            osgViewer::View* view2 = new osgViewer::View;
            view2->getCamera()->setGraphicsContext(viewerWindow->getGraphicsWindow());
            view2->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width)/static_cast<double>(height/2), 1.0, 1000.0);
            view2->getCamera()->setViewport(new osg::Viewport(0,height/2,width,height/2));
            view2->setCameraManipulator(new osgGA::TrackballManipulator);
            view2->setSceneData(loadedModel.get());
            
            viewerWindow->addView(view2);
        }

        viewerWindow->show();
    }
    else
    {
        ViewerQT* viewerWindow = new ViewerQT;

        viewerWindow->setCameraManipulator(new osgGA::TrackballManipulator);
        viewerWindow->setModelData( loadedModel.get() );

        viewerWindow->show();
    }    
    
    
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
   
    return a.exec();
}

