
#ifndef _REPLACEMATGROUPGRAPHOP_H_
#define _REPLACEMATGROUPGRAPHOP_H_

// OpenSG includes
#include <OpenSG/OSGGraphOp.h>
#include <OpenSG/OSGMaterial.h>

// std library includes
#include <vector>

class ReplaceMatGroupGraphOp : public OSG::GraphOp
{
  public:
    typedef OSG::GraphOp           Inherited;
    typedef ReplaceMatGroupGraphOp Self;

    /*=======================================================================*/
    /* Construction/Destruction                                              */
    
             ReplaceMatGroupGraphOp(void);
    virtual ~ReplaceMatGroupGraphOp(void);
    
    virtual OSG::GraphOp* create(void);
    
    /*=======================================================================*/
    /* Traversal                                                             */
    
    virtual bool traverse(OSG::NodePtr& root);
    
    /*=======================================================================*/
    /* Parameters                                                            */
    
    virtual void        setParams(const std::string params);
    virtual std::string usage    (void                    );
    
  protected:
    virtual OSG::Action::ResultE traverseEnter(OSG::NodePtr&        node );
    virtual OSG::Action::ResultE traverseLeave(OSG::NodePtr&        node,
                                               OSG::Action::ResultE res  );
    
    OSG::NodePtr findCommonMatGroup(OSG::NodeCorePtr pCore   );
    bool         isParent(OSG::NodePtr pParent, OSG::NodePtr          pChild);
    bool         isParent(OSG::NodePtr pParent, OSG::MFNodePtr const &nodes );    
                             
    typedef std::vector<OSG::MaterialPtr> MaterialStack;
    
    MaterialStack _matStack;
};

#endif // _REPLACEMATGROUPGRAPHOP_H_
