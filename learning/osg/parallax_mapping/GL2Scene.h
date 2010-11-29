
#include <osg/Node>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <osg/Program>

class GL2Scene : public osg::Referenced
{
    public:
	GL2Scene();

	osg::ref_ptr<osg::Group> getRootNode() { return _rootNode; }
	void reloadShaderSource();
	void toggleShaderEnable();

    protected:
	~GL2Scene();

    private:	/*methods*/
	osg::ref_ptr<osg::Group> buildScene();

    private:	/*data*/
	osg::ref_ptr<osg::Group> _rootNode;
	std::vector< osg::ref_ptr<osg::Program> > _programList;
	bool _shadersEnabled;
};

typedef osg::ref_ptr<GL2Scene> GL2ScenePtr;


