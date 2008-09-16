
#include <NamedObjectCache.h>

// VRJuggler includes
#include <vpr/Util/Debug.h>


    NamedObjectCache::NamedObjectCache(void)
    
    : _root  (),
      _objMap()
{
}

    NamedObjectCache::~NamedObjectCache(void)
{
    // nothing to do
}

OSG::NodePtr
    NamedObjectCache::getRoot(void) const
{
    return _root;
}
    
void
    NamedObjectCache::setRoot(OSG::NodePtr const &root)
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
    
    if(_root != OSG::NullFC)
    {
        OSG::traverse(
            _root,
            OSG::osgTypedMethodFunctor1ObjPtrCPtrRef<OSG::Action::ResultE,
                                                     Self,
                                                     OSG::NodePtr         >(
                this, &Self::traverseEnter));
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
           
        OSG::NodePtr pNode = OSG::NodePtr::dcast(omIt->second.get());
        
        if(pNode != OSG::NullFC)
        {
            os << " core type [" << pNode->getCore()->getType().getCName()
               << "]";
        }
        
        os << "\n";
    }
}

OSG::Action::ResultE
    NamedObjectCache::traverseEnter(OSG::NodePtr& node)
{
    if(node == OSG::NullFC)
        return OSG::Action::Continue;
        
    std::string nodeName;
        
    if(OSG::getName(node) != NULL)
    {
        nodeName = OSG::getName(node);
        
        _objMap.insert(
            ObjectMap::value_type(nodeName, OSG::FieldContainerRefPtr(node)));
    }
    
    OSG::NodeCorePtr pCore = node->getCore();
    
    if(pCore == OSG::NullFC)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "NamedObjectCache::traverseEnter: Node without core.\n"
            << vprDEBUG_FLUSH;    
    
        return OSG::Action::Continue;
    }
    
    std::string coreName;
    
    if(OSG::getName(pCore) != NULL)
    {
        coreName = OSG::getName(pCore);
        
        _objMap.insert(
            ObjectMap::value_type(coreName, OSG::FieldContainerRefPtr(pCore)));
    }
    
    return OSG::Action::Continue;
}
