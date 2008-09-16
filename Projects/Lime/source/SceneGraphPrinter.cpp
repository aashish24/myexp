

#include <SceneGraphPrinter.h>

// OpenSG includes
#include <OpenSG/OSGSimpleAttachments.h>

    SceneGraphPrinter::SceneGraphPrinter(OSG::NodePtr root)
    
    : _pRoot  (root),
      _pStream(NULL),
      _indent (0)
{
    // nothing to do
}

void
    SceneGraphPrinter::print(std::ostream &os)
{
    _pStream = &os;
    _indent  = 0;
    
    OSG::traverse(
        _pRoot,
        OSG::osgTypedMethodFunctor1ObjPtrCPtrRef<
            OSG::Action::ResultE,
            SceneGraphPrinter,
            OSG::NodePtr         >(this, &Self::traverseEnter),
        OSG::osgTypedMethodFunctor2ObjPtrCPtrRef<
            OSG::Action::ResultE,
            SceneGraphPrinter,
            OSG::NodePtr,
            OSG::Action::ResultE >(this, &Self::traverseLeave));
}

OSG::Action::ResultE
    SceneGraphPrinter::traverseEnter(OSG::NodePtr &node)
{
    if(node == OSG::NullFC)
        return OSG::Action::Continue;
    
    std::ostream &os = *_pStream;
    incIndent();
    
    indentStream(os)
        <<   "[" << node.getCPtr()
        << "] [" << (OSG::getName(node) ? OSG::getName(node) : "-")
        << "]";
    
    OSG::NodeCorePtr pCore = node->getCore();
    
    if(pCore == OSG::NullFC)
    {
        os << "\n";
        return OSG::Action::Continue;
    }
    
    os << " -- [" << pCore.getCPtr() << "]"
       <<    " [" << pCore->getType().getCName() << "]";
    
    os << " [" << (OSG::getName(pCore) ? OSG::getName(pCore) : "-")
       << "]";
    
    OSG::MFNodePtr::const_iterator pIt  = pCore->getParents().begin();
    OSG::MFNodePtr::const_iterator pEnd = pCore->getParents().end  ();
    
    os << " -- [" << pCore->getParents().size() << "] parents";
    
//     for(; pIt != pEnd; ++pIt)
//     {
//         os << " ["  << node.getCPtr()
//            << "] [" << (OSG::getName(node) ? OSG::getName(node) : "-")
//            << "]";
//     }
    
    os << "\n";
    return OSG::Action::Continue;
}

OSG::Action::ResultE
    SceneGraphPrinter::traverseLeave(OSG::NodePtr &node, OSG::Action::ResultE res)
{
    if(node == OSG::NullFC)
        return OSG::Action::Continue;
    
    decIndent();
    
    return OSG::Action::Continue;
}

