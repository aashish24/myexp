
#include <ObjectRenamer.h>

#include <PathHandler.h>

// OpenSG includes
//#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGNameAttachment.h>

// VRJuggler includes
#include <vpr/Util/Debug.h>

// std library includes
#include <ostream>

// boost includes
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>

namespace bs = boost::spirit;


    ObjectRenamer::ObjectRenamer(void)
    
    : _pRoot       (),
      _nameMap     ()
{
}

void
    ObjectRenamer::readFile(std::string const &fileName)
{
    typedef char                               char_t;
    typedef bs::file_iterator<char_t>          FileItType;
   
    typedef boost::tokenizer<
        boost::escaped_list_separator<char>,
        FileItType                           > TokenizerType;

    FileItType fileIt(fileName);
        
    if(!fileIt)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL) 
            << "ObjectRenamer::readFile: Could not open name mapping file "
            << "'" << fileName << "'.\n"
            << vprDEBUG_FLUSH;
            
        return;
    }
    
    FileItType fileEnd = fileIt.make_end();
                                                          
    TokenizerType tok(fileIt, fileEnd);
    TokenizerType::iterator tokIt  = tok.begin();
    TokenizerType::iterator tokEnd = tok.end  ();
    
    while(tokIt != tokEnd)
    {
        std::string objName = *tokIt;
                
        if(++tokIt == tokEnd)
            break;
        
        std::string objId   = *tokIt;
                
        boost::trim(objName);
        boost::trim(objId  );
        
        std::pair<NameMap::iterator, bool> res = 
            _nameMap.insert(NameMap::value_type(objId, objName));
            
        if(res.second == false)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                << "ObjectRenamer::readFile: Could not insert mapping ["
                << objId << "] -> [" << objName << "]\n"
                << vprDEBUG_FLUSH;
        }
        
        ++tokIt;
    }
}

void 
    ObjectRenamer::apply(void)
{
  // @todo: Ask carsten. 
  /*
    OSG::traverse(
        _pRoot,
        OSG::osgTypedMethodFunctor1ObjPtrCPtrRef<
            OSG::Action::ResultE,
            Self,
            OSG::NodePtr         >(this, &Self::traverseEnter));
 */
  OSG::traverse(_pRoot.get(), boost::bind(&Self::traverseEnter, this, _1));
}

void
    ObjectRenamer::dump(std::ostream &os) const
{
    os << "ObjectRenamer: \n";
    
    NameMap::const_iterator nmIt  = _nameMap.begin();
    NameMap::const_iterator nmEnd = _nameMap.end  ();
    
    for(; nmIt != nmEnd; ++nmIt)
    {
        os << " [" << nmIt->first << "] -> [" << nmIt->second << "]\n";
    }
}

OSG::Action::ResultE
    ObjectRenamer::traverseEnter(OSG::Node *pNode)
{
    if(!pNode)
        return OSG::Action::Continue;

    if(OSG::getName(pNode) == NULL)
        return OSG::Action::Continue;
        
    std::string nodeName = OSG::getName(pNode);
    
    NameMap::const_iterator nodeIt = _nameMap.find(nodeName);
    
    if(nodeIt != _nameMap.end())
    {
        OSG::setName(pNode, nodeIt->second);
    }
    
    // rename the core
    OSG::NodeCoreRefPtr pCore = pNode->getCore();
    
    if(!pCore)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "ObjectRenamer::traverseEnter: Node without core.\n"
            << vprDEBUG_FLUSH;    
    
        return OSG::Action::Continue;
    }
    
    if(OSG::getName(pCore) == NULL)
        return OSG::Action::Continue;
        
    std::string coreName = OSG::getName(pNode);
    
    NameMap::const_iterator coreIt = _nameMap.find(coreName);
    
    if(coreIt != _nameMap.end())
    {
        OSG::setName(pCore, coreIt->second);
    }
    
    return OSG::Action::Continue;
}
