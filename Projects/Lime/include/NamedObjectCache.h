
#ifndef _NAMEDOBJECTCACHE_H_
#define _NAMEDOBJECTCACHE_H_

// OpenSG includes
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGFieldContainer.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGSimpleAttachments.h>

// std library includes
#include <iosfwd>
#include <map>
#include <string>

class NamedObjectCache
{
  public:
    typedef NamedObjectCache Self;
  
    typedef std::map<std::string, OSG::FieldContainerRefPtr> ObjectMap;
    
    explicit  NamedObjectCache(void);
    
             ~NamedObjectCache(void);
  
    /*=======================================================================*/
    /* Setup                                                                 */
    /*=======================================================================*/
             
    OSG::NodePtr getRoot(void                    ) const;
    void         setRoot(OSG::NodePtr const &root);
    
    /*=======================================================================*/
    /* Cache access                                                          */
    /*=======================================================================*/
    
    void                      refresh  (void                   );
    OSG::FieldContainerRefPtr getObject(std::string const &name) const;
  
    /*=======================================================================*/
    /* Access                                                                */
    /*=======================================================================*/
    
    // direct storage access -- avoid using these, if possible
    ObjectMap const &getObjectMap (void) const;
    ObjectMap       &editObjectMap(void);
    
    void dump(std::ostream &os) const;
    
  private:  
    OSG::Action::ResultE traverseEnter(OSG::NodePtr& node);
    
    OSG::NodePtr _root;
    ObjectMap    _objMap;
};


inline NamedObjectCache::ObjectMap const &
    NamedObjectCache::getObjectMap(void) const
{
    return _objMap;
}

inline NamedObjectCache::ObjectMap &
    NamedObjectCache::editObjectMap(void)
{
    return _objMap;
}

#endif // _NAMEDOBJECTCACHE_H_
