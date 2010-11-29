
#include <osg/Notify>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>

#include "GL2Scene.h"

using namespace osg;

///////////////////////////////////////////////////////////////////////////

class KeyHandler: public osgGA::GUIEventHandler
{
    public:
        KeyHandler( GL2ScenePtr gl2Scene ) :
                _gl2Scene(gl2Scene)
        {}

        bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& )
        {
            if( ea.getEventType() != osgGA::GUIEventAdapter::KEYDOWN )
                return false;

            switch( ea.getKey() )
            {
                case 'x':
                    _gl2Scene->reloadShaderSource();
                    return true;
                case 'y':
                    _gl2Scene->toggleShaderEnable();
                    return true;
            }
            return false;
        }

    private:
        GL2ScenePtr _gl2Scene;
};

///////////////////////////////////////////////////////////////////////////

int main(int, char **)
{
    // construct the viewer.
    osgViewer::Viewer viewer;

    // create the scene
    GL2ScenePtr gl2Scene = new GL2Scene;

    viewer.setSceneData( gl2Scene->getRootNode().get() );

    viewer.addEventHandler( new KeyHandler(gl2Scene) );

    return viewer.run();
}

/*EOF*/

