
#include "osg/Node"
#include "osg/Referenced"
#include "osg/ref_ptr"

#include "osg/Program"

class SceneManager : public osg::Referenced
{
  public:
    SceneManager();

    osg::ref_ptr< osg::Group > getRootNode() { return mRootNode; }
    
    void reloadShaderSource();
    void toggleShaderEnable();

    void update();

  protected:
	  ~SceneManager();

  private:	

	  osg::ref_ptr<osg::Group> buildScene();

  private:	
	  
    osg::ref_ptr<osg::Group>                  mRootNode;
	  
    std::vector< osg::ref_ptr<osg::Program> > mProgramList;
	  
    bool                                      mShadersEnabled;
};

