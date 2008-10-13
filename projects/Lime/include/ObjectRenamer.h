
#ifndef _OBJECTRENAMER_H_
#define _OBJECTRENAMER_H_

#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGNode.h>

// std library includes
#include <iosfwd>
#include <map>
#include <string>

// forward declarations
class PathHandler;


class ObjectRenamer
{
  public:
    typedef ObjectRenamer                      Self;
    
    typedef std::map<std::string, std::string> NameMap;

    explicit ObjectRenamer(void);
    
    void readFile(std::string const &fileName);
    void apply   (void                       );
       
    OSG::NodeRefPtr getRoot(void              ) const;
    void         setRoot(OSG::NodeRefPtr pRoot);
    
    NameMap const &getNameMap (void) const;
    NameMap       &editNameMap(void);
    
    void dump(std::ostream &os) const;
    
  private:
    OSG::Action::ResultE traverseEnter(OSG::Node  *node);
    
    OSG::NodeRefPtr _pRoot;
    NameMap      _nameMap;
};

inline OSG::NodeRefPtr
    ObjectRenamer::getRoot(void) const
{
    return _pRoot;
}

inline void
    ObjectRenamer::setRoot(OSG::NodeRefPtr pRoot)
{
    _pRoot = pRoot;
}

inline ObjectRenamer::NameMap const &
    ObjectRenamer::getNameMap(void) const
{
    return _nameMap;
}

inline ObjectRenamer::NameMap &
    ObjectRenamer::editNameMap(void)
{
    return _nameMap;
}

#endif // _OBJECTRENAMER_H_
