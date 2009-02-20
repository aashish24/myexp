
#ifndef __VRJ_APP_H__
#define __VRJ_APP_H__

#include "SimFlow/Scene/SceneManager.h"

#include "VrjCore/OsgVJApp.h"

#include "VrjInteraction.h"

#include "osg/Texture2D"

#include <map>

class VrjApp : public OsgVJApp 
{
	public:

    typedef std::vector< osg::ref_ptr< osg::Texture2D > >       Textures;
    typedef std::map< std::string, osg::ref_ptr< osg::Node > >  Groups;

		VrjApp( vrj::Kernel* kern, int& argc, char** argv );
		
    ~VrjApp()
    {
    }

    osg::Group*                                   createDashboard();

		void                                          appInit();		
		void                                          appBufferPreDraw();	
	  void                                          appSceneInit();	
		void                                          appPreFrame();
		void                                          appLatePreFrame();		

		void																					addSceneLight();
	private:			

    Textures                                      mTextures;

    Groups                                        mGroups;

		VrjInteraction*                               mInteraction;

		osg::ref_ptr< osg::MatrixTransform >					mRoot;

    osg::ref_ptr< SimFlow::Scene::SceneManager >  mSceneManager;
    
};

#endif // __VRJ_APP_H__

