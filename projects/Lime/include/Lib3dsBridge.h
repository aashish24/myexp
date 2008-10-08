
#ifndef _LIB3DSBRIDGE_H_
#define _LIB3DSBRIDGE_H_

// OpenSG includes
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGNode.h>

// lib3ds includes
#include <lib3ds/types.h>

// std library includes
#include <map>
#include <string>
#include <vector>


class Lib3dsBridge
{
  public:
    typedef Lib3dsBridge Self;
  
    struct NodeMapEntry
    {
        NodeMapEntry(Lib3dsNode *pLNode, OSG::NodeRefPtr pNode);
        
Lib3dsNode   		*_pLNode;
        OSG::NodeRefPtr _pNode;
    };
    
    typedef std::vector<NodeMapEntry>             NodeMap;
    typedef std::map   <std::string, std::string> NameMap;
      
    Lib3dsBridge(void);

    void            setLib3dsFile   (Lib3dsFile *pLFile);
    Lib3dsFile*     getLib3dsFile   (void              ) const; 
    
    void            setNameMap      (NameMap const     &nameMap );
    NameMap const   &getNameMap     (void                       ) const;
    NameMap         &editNameMap    (void                       );
    void            readNameMapFile (std::string const &fileName);
    
    void            dumpNameMap     (void                       ) const;
    
    OSG::NodeRefPtr construct       (void);
    void            update          (void);
    
    OSG::NodeRefPtr getRoot         (void) const;

  private:
    void                constructScene    (Lib3dsNode   *pLNode,
                                           OSG::NodeRefPtr  pNode  );

    OSG::GeometryRefPtr constructGeometry (Lib3dsMesh   *pLMesh );
    
    void                lookupName        (std::string const &oldName,
                                           std::string       &newName );
    
    NodeMap          _nodeMap;
    NameMap          _nameMap;
    Lib3dsFile      *_pLFile;
    OSG::NodeRefPtr  _pRoot;
};

inline void
    Lib3dsBridge::setLib3dsFile(Lib3dsFile *pLFile)
{
    _pLFile = pLFile;
}

inline Lib3dsFile *
    Lib3dsBridge::getLib3dsFile(void) const
{
    return _pLFile;
}

inline void
    Lib3dsBridge::setNameMap(NameMap const &nameMap)
{
    _nameMap = nameMap;
}

inline Lib3dsBridge::NameMap const &
    Lib3dsBridge::getNameMap(void) const
{
    return _nameMap;
}

inline Lib3dsBridge::NameMap &
    Lib3dsBridge::editNameMap(void)
{
    return _nameMap;
}

inline OSG::NodeRefPtr
    Lib3dsBridge::getRoot(void) const
{
    return _pRoot.get();
}


inline
    Lib3dsBridge::NodeMapEntry::NodeMapEntry(
        Lib3dsNode *pLNode, OSG::NodeRefPtr pNode)
    : _pLNode(pLNode),
      _pNode (pNode )
{
    // nothing to do
}

# endif // _LIB3DSBRIDGE_H_
