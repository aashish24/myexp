
#include "osg/Notify"
#include "osgGA/GUIEventAdapter"
#include "osgGA/GUIActionAdapter"
#include "osgDB/ReadFile"
#include "osgUtil/Optimizer"
#include "osgViewer/Viewer"

#include "SceneManager.h"

///////////////////////////////////////////////////////////////////////////

int main(int, char **)
{
    // construct the viewer.
    osgViewer::Viewer viewer;

    // create the scene
    GL2ScenePtr gl2Scene = new SceneManager;

    viewer.setSceneData( gl2Scene->getRootNode().get() );

    return viewer.run();
}

