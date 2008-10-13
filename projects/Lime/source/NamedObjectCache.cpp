
#include <NamedObjectCache.h>

// OpenSG includes. 
#include <OpenSG/OSGNameAttachment.h>

// VRJuggler includes
#include <vpr/Util/Debug.h>

#include <boost/bind.hpp>

    NamedObjectCache::NamedObjectCache(void)
    
    : _root  (),
      _objMap()
{
}

    NamedObjectCache::~NamedObjectCache(void)
{
    // nothing to do
}

OSG::NodeRefPtr
    NamedObjectCache::getRoot(void) const
{
    return _root;
}
    
void
    NamedObjectCache::setRoot(OSG::NodeRefPtr const &root)
{
    if(_root != root)
    {
        _root = root;
        refresh();
    }
}
            
void
    NamedObjectCache::refresh(void)
{
    _objMap.clear();
    
    if(_root)
    {
        // @todo: Figure out the right functor. 
        /*
        OSG::traverse(
            _root,
            OSG::osgTypedMethodFunctor1ObjPtrCPtrRef<OSG::Action::ResultE,
                                                     Self,
                                                     OSG::NodeRefPtr         >(
                this, &Self::traverseEnter));
        */
        OSG::traverse(_root, boost::bind(&Self::traverseEnter, this, _1));
    }
}
    
OSG::FieldContainerRefPtr
    NamedObjectCache::getObject(std::string const &name) const
{
    OSG::FieldContainerRefPtr pFC;
    ObjectMap::const_iterator omIt = _objMap.find(name);
    
    if(omIt != _objMap.end())
    {
        pFC = omIt->second;
    }
    
    return pFC;
}

void
    NamedObjectCache::dump(std::ostream &os) const
{
    ObjectMap::const_iterator omIt  = _objMap.begin();
    ObjectMap::const_iterator omEnd = _objMap.end  ();
    
    for(; omIt != omEnd; ++omIt)
    {
        os << "Object [" << omIt->first
           << "] type [" << omIt->second->getType().getCName() << "]";
           
        OSG::NodeRefPtr pNode = OSG::dynamic_pointer_cast<OSG::Node>(omIt->second);
        
        if(pNode)
        {
            os << " core type [" << pNode->getCore()->getType().getCName()
               << "]";
        }
        
        os << "\n";
    }
}

OSG::Action::ResultE
    NamedObjectCache::traverseEnter(OSG::Node *node)
{
    if(!node)
        return OSG::Action::Continue;
        
    std::string nodeName;
        
    if(OSG::getName(node) != NULL)
    {
        nodeName = OSG::getName(node);
        
        _objMap.insert(
            ObjectMap::value_type(nodeName, OSG::FieldContainerRefPtr(node)));
    }
    
    OSG::NodeCoreRefPtr pCore = node->getCore();
    
    if(!pCore)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "NamedObjectCache::traverseEnter: Node without core.\n"
            << vprDEBUG_FLUSH;    
    
        return OSG::Action::Continue;
    }
    
    std::string coreName;
    
    if(OSG::getName(pCore.get()) != NULL)
    {
        coreName = OSG::getName(pCore.get());
        
        _objMap.insert(
            ObjectMap::value_type(coreName, OSG::FieldContainerRefPtr(pCore)));
    }
    
    return OSG::Action::Continue;
}
