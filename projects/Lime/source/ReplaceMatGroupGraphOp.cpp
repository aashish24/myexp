
#include <ReplaceMatGroupGraphOp.h>

// OpenSG includes
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialDrawable.h>

// VRJuggler includes
#include <vpr/Util/Debug.h>

    ReplaceMatGroupGraphOp::ReplaceMatGroupGraphOp(void)
    
    : Inherited("ReplaceMatGroupGraphOp")
{
    // nothing to do
}

    ReplaceMatGroupGraphOp::~ReplaceMatGroupGraphOp(void)
{
    // nothing to do
}

OSG::GraphOp*
    ReplaceMatGroupGraphOp::create(void)
{
    return new ReplaceMatGroupGraphOp();
}

bool
    ReplaceMatGroupGraphOp::traverse(OSG::NodePtr& root)
{
    if (!Inherited::traverse(root))
    {
        return false;
    }
    
    return true;
}


void
    ReplaceMatGroupGraphOp::setParams(const std::string params)
{
}
   
std::string
    ReplaceMatGroupGraphOp::usage(void)
{
    return "Push Materials from MaterialGroups into Geometry and replace "
           "MaterialGroup with Group cores.";
}

OSG::Action::ResultE
    ReplaceMatGroupGraphOp::traverseEnter(OSG::NodePtr& node)
{
    if(node == OSG::NullFC)
        return OSG::Action::Continue;
        
    if(node->getCore() == OSG::NullFC)
        return OSG::Action::Continue;
        
    OSG::MaterialGroupPtr pMatGroup =
        OSG::MaterialGroupPtr::dcast(node->getCore());
        
    if(pMatGroup != OSG::NullFC)
    {
        _matStack.push_back(pMatGroup->getMaterial());
        
        return OSG::Action::Continue;
    }
    
    OSG::MaterialDrawablePtr pMatDraw =
        OSG::MaterialDrawablePtr::dcast(node->getCore());
        
    if(pMatDraw != OSG::NullFC)
    {
        if(pMatDraw->getParents().size() > 1)
        {
            OSG::NodePtr pCommonMG = findCommonMatGroup(pMatDraw);
            
            if(pCommonMG == OSG::NullFC)
            {
                vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
                    << "ReplaceMatGroupGraphOp::traverseEnter: "
                    << "MaterialDrawable is shared, can NOT change material.\n"
                    << vprDEBUG_FLUSH;
                                
                return OSG::Action::Continue;
            }
        }
        
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "ReplaceMatGroupGraphOp::traverseEnter: "
            << "Pushing Material to MaterialDrawable.\n"
            << vprDEBUG_FLUSH;
            
        OSG::beginEditCP(pMatDraw);
            pMatDraw->setMaterial(_matStack.back());
        OSG::endEditCP  (pMatDraw);
    }
    
    return OSG::Action::Continue;
}

OSG::Action::ResultE
    ReplaceMatGroupGraphOp::traverseLeave(
        OSG::NodePtr& node, OSG::Action::ResultE res)
{
    if(node == OSG::NullFC)
        return OSG::Action::Continue;
        
    if(node->getCore() == OSG::NullFC)
        return OSG::Action::Continue;
        
    OSG::MaterialGroupPtr pMatGroup =
        OSG::MaterialGroupPtr::dcast(node->getCore());
        
    if(pMatGroup != OSG::NullFC)
    {
        _matStack.pop_back();
        
        OSG::beginEditCP(node, OSG::Node::CoreFieldMask);
            node->setCore(OSG::Group::create());
        OSG::endEditCP  (node, OSG::Node::CoreFieldMask);
    }
    
    return OSG::Action::Continue;
}

OSG::NodePtr
    ReplaceMatGroupGraphOp::findCommonMatGroup(OSG::NodeCorePtr pCore)
{
    OSG::NodePtr pNode = pCore->getParents()[0];
    
    while(true)
    {
        if(pNode == OSG::NullFC)
            break;
    
        OSG::NodeCorePtr pCurrCore = pNode->getCore();
        
        if(OSG::MaterialGroupPtr::dcast(pCurrCore) != OSG::NullFC)
        {
            if(isParent(pNode, pCurrCore->getParents()))
                return pNode;
        }
        
        pNode = pNode->getParent();
    }
    
    return pNode;
}

bool
    ReplaceMatGroupGraphOp::isParent(OSG::NodePtr pParent, OSG::NodePtr pChild)
{
    while(true)
    {
        if(pChild == OSG::NullFC)
            return false;
            
        if(pChild == pParent)
            return true;
            
        pChild = pChild->getParent();
    }
    
    return false;
}

bool
    ReplaceMatGroupGraphOp::isParent(
        OSG::NodePtr pParent, OSG::MFNodePtr const &nodes)
{
    OSG::MFNodePtr::const_iterator nIt  = nodes.begin();
    OSG::MFNodePtr::const_iterator nEnd = nodes.end  ();
    
    for(; nIt != nEnd; ++nIt)
    {
        if(!isParent(pParent, *nIt))
            return false;
    }
    
    return true;
}
