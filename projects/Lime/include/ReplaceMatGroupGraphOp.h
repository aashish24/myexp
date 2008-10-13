
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
    
    virtual bool traverse(OSG::Node *root);
    
    /*=======================================================================*/
    /* Parameters                                                            */
    
    virtual void        setParams(const std::string params);
    virtual std::string usage    (void                    );
    
  protected:
    virtual OSG::Action::ResultE traverseEnter(OSG::Node*        const node );
    virtual OSG::Action::ResultE traverseLeave(OSG::Node*        const node,
                                               OSG::Action::ResultE res  );
    
    OSG::NodeRefPtr findCommonMatGroup(OSG::NodeCoreRefPtr pCore   );
    bool            isParent(OSG::NodeRefPtr pParent, OSG::NodeRefPtr          pChild);
    //bool            isParent(OSG::NodeRefPtr pParent, OSG::MFNodeRefPtr const &nodes ); 
    bool            isParent(OSG::NodeRefPtr pParent, OSG::MFParentFieldContainerPtr const &nodes );   
                             
    typedef std::vector<OSG::MaterialRefPtr> MaterialStack;
    
    MaterialStack _matStack;
};

#endif // _REPLACEMATGROUPGRAPHOP_H_
