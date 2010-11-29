
#include "osg/Node"
#include "osg/Referenced"
#include "osg/ref_ptr"

#include "osg/Program"

class SceneManager : public osg::Referenced
{
  public:
    SceneManager();

    osg::ref_ptr< osg::Group > getRootNode() { return _rootNode; }
    
    void reloadShaderSource();
    void toggleShaderEnable();
  
  protected:
	  ~SceneManager();

  private:	

	  osg::ref_ptr<osg::Group> buildScene();

  private:	
	  
    osg::ref_ptr<osg::Group>                  _rootNode;
	  
    std::vector< osg::ref_ptr<osg::Program> > _programList;
	  
    bool                                      _shadersEnabled;
};

