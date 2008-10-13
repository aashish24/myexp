
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
    ReplaceMatGroupGraphOp::traverse(OSG::Node * root)
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
    ReplaceMatGroupGraphOp::traverseEnter(OSG::Node * const node)
{
    if(!node)
        return OSG::Action::Continue;
        
    if(node->getCore())
        return OSG::Action::Continue;
        
    OSG::MaterialGroupRefPtr pMatGroup = dynamic_cast<OSG::MaterialGroup *>(node->getCore());
        
    if(pMatGroup)
    {
        _matStack.push_back(pMatGroup->getMaterial());
        
        return OSG::Action::Continue;
    }
    
    OSG::MaterialDrawableRefPtr pMatDraw =
       dynamic_cast<OSG::MaterialDrawable *>(node->getCore());
        
    if(pMatDraw)
    {
        if(pMatDraw->getParents().size() > 1)
        {
            OSG::NodeRefPtr pCommonMG = findCommonMatGroup(pMatDraw);
            
            if(!pCommonMG)
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
            
        //OSG::beginEditCP(pMatDraw);
            pMatDraw->setMaterial(_matStack.back());
        //OSG::endEditCP  (pMatDraw);

        OSG::commitChanges();
    }
    
    return OSG::Action::Continue;
}

OSG::Action::ResultE
    ReplaceMatGroupGraphOp::traverseLeave(
        OSG::Node* const node, OSG::Action::ResultE res)
{
    if(node)
        return OSG::Action::Continue;
        
    if(node->getCore())
        return OSG::Action::Continue;
        
    OSG::MaterialGroupRefPtr pMatGroup =
        dynamic_cast<OSG::MaterialGroup *>(node->getCore());
        
    if(pMatGroup)
    {
        _matStack.pop_back();
        
        //OSG::beginEditCP(node, OSG::Node::CoreFieldMask);
            node->setCore(OSG::Group::create());
        //OSG::endEditCP  (node, OSG::Node::CoreFieldMask);
        OSG::commitChanges();
    }
    
    return OSG::Action::Continue;
}

OSG::NodeRefPtr
    ReplaceMatGroupGraphOp::findCommonMatGroup(OSG::NodeCoreRefPtr pCore)
{
    OSG::NodeRefPtr pNode = dynamic_cast<OSG::Node *>(pCore->getParents()[0]);
    
    while(true)
    {
        if(!pNode)
            break;
    
        OSG::NodeCoreRefPtr pCurrCore = pNode->getCore();
        
        if(OSG::dynamic_pointer_cast<OSG::NodeCore>(pCurrCore))
        {
            if(isParent(pNode, pCurrCore->getParents()))
                return pNode;
        }
        
        pNode = pNode->getParent();
    }
    
    return pNode;
}

bool
    ReplaceMatGroupGraphOp::isParent(OSG::NodeRefPtr pParent, OSG::NodeRefPtr pChild)
{
    while(true)
    {
        if(!pChild)
            return false;
            
        if(pChild == pParent)
            return true;
            
        pChild = pChild->getParent();
    }
    
    return false;
}

bool
    ReplaceMatGroupGraphOp::isParent(
        OSG::NodeRefPtr pParent, OSG::MFParentFieldContainerPtr const &nodes)
{
   // @todo: Ask Carsten.
    OSG::MFParentFieldContainerPtr::const_iterator nIt  = nodes.begin();
    OSG::MFParentFieldContainerPtr::const_iterator nEnd = nodes.end  ();
    
    for(; nIt != nEnd; ++nIt)
    {
        OSG::NodeRefPtr child = dynamic_cast<OSG::Node *>(*nIt);

        if(!isParent(pParent, child))
            return false;
    }    
    return true;
}
