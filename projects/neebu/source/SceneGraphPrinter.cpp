
#include <OpenSG/OSGNameAttachment.h>

#include <SceneGraphPrinter.h>
#include <boost/bind.hpp>

// OpenSG includes
//#include <OpenSG/OSGSimpleAttachments.h>

    SceneGraphPrinter::SceneGraphPrinter(OSG::NodeRefPtr root)
    
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

    OSG::traverse( _pRoot.get(),
                   boost::bind(&Self::traverseEnter, this, _1    ),
                   boost::bind(&Self::traverseLeave, this, _1, _2));
}

OSG::Action::ResultE
    SceneGraphPrinter::traverseEnter(OSG::Node *node)
{
    if(!node)
        return OSG::Action::Continue;
    
    std::ostream &os = *_pStream;
    incIndent();
    
    indentStream(os)
        <<   "[" << node
        << "] [" << (OSG::getName(node) ? OSG::getName(node) : "-")
        << "]";
    
    OSG::NodeCoreRefPtr pCore = node->getCore();
    
    if(!pCore)
    {
        os << "\n";
        return OSG::Action::Continue;
    }
    
    os << " -- [" << pCore.get() << "]"
       <<    " [" << pCore->getType().getCName() << "]";
    
    os << " [" << (OSG::getName(pCore) ? OSG::getName(pCore) : "-")
       << "]";
    
    //OSG::MFNodeRefPtr::const_iterator pIt  = pCore->getParents().begin();
    //OSG::MFNodeRefPtr::const_iterator pEnd = pCore->getParents().end  ();
    
    OSG::MFParentFieldContainerPtr::const_iterator pIt  = pCore->getParents().begin();
    OSG::MFParentFieldContainerPtr::const_iterator pEnd = pCore->getParents().end  ();

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
    SceneGraphPrinter::traverseLeave(OSG::Node *node, OSG::Action::ResultE res)
{
    if(!node)
        return OSG::Action::Continue;
    
    decIndent();
    
    return OSG::Action::Continue;
}

