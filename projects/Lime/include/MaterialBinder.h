
#ifndef _MATERIALBINDER_H_
#define _MATERIALBINDER_H_

// OpenSG includes
#include <OpenSG/OSGMaterialDrawable.h>
#include <OpenSG/OSGMaterialGroup.h>

// boost includes
#include <boost/regex.hpp>

// std library includes
#include <iosfwd>
#include <deque>

// forward declarations
class MaterialDesc;
class MaterialManager;
class NamedObjectCache;
class PathHandler;


class MaterialBinder
{
  public:
    typedef std::pair <boost::regex, std::string> BindingMapEntry;
    typedef std::deque<BindingMapEntry          > BindingMap;
    
    explicit  MaterialBinder(void);
    
             ~MaterialBinder(void);
    
    /*=======================================================================*/
    /* Setup                                                                 */
    /*=======================================================================*/
                 
    void                   setMatManager(MaterialManager const *pMatMgr);
    MaterialManager const *getMatManager(void                          ) const;
    
    void                    setObjCache(NamedObjectCache const *pObjCache);
    NamedObjectCache const *getObjCache(void                             ) const;
    
    /*=======================================================================*/
    /* Apply                                                                 */
    /*=======================================================================*/
    
    void apply(void                                   );
    void apply(std::string const &objName,
               std::string const &matName,
               bool               storeBinding = false);
    
    /*=======================================================================*/
    /* Bindings                                                              */
    /*=======================================================================*/
               
    void addBindingFront(std::string const &objName,
                         std::string const &matName );
    void addBindingBack (std::string const &objName,
                         std::string const &matName );
    void setBinding     (std::string const &objName,
                         std::string const &matName );
    
    bool findBinding(std::string const   &objName,
                     std::string         &matName,
                     bool                 matchObjLiteral = false);
    bool findBinding(std::string const   &objName,
                     OSG::MaterialRefPtr &pMat,
                     bool                 matchObjLiteral = false);
    
    void readFile  (std::string const &fileName );
               
    /*=======================================================================*/
    /* Access                                                                */
    /*=======================================================================*/
    
    BindingMap const &getBindingMap (void) const;
    BindingMap       &editBindingMap(void);

    void dump(std::ostream &os);
    
  private:
    void bindMaterialDrawable(std::string const             &objName,
                              OSG::MaterialDrawableRefPtr  pMatDraw );

    void bindMaterialGroup   (std::string const             &objName,
                              OSG::MaterialGroupRefPtr      pMatGroup);

    bool findMaterial        (std::string const             &objName,
                              OSG::MaterialRefPtr           &pMat,
                              MaterialDesc const            *&pMatDesc,
                              std::string                   &matName  );
  
    MaterialManager  const *_pMatMgr;
    NamedObjectCache const *_pObjCache;
    BindingMap              _bindMap;
};


inline void
    MaterialBinder::setMatManager(MaterialManager const *pMatMgr)
{
    _pMatMgr = pMatMgr;
}

inline MaterialManager const *
    MaterialBinder::getMatManager(void) const
{
    return _pMatMgr;
}

inline void
    MaterialBinder::setObjCache(NamedObjectCache const *pObjCache)
{
    _pObjCache = pObjCache;
}

inline NamedObjectCache const *
    MaterialBinder::getObjCache(void) const
{
    return _pObjCache;
}

inline MaterialBinder::BindingMap const &
    MaterialBinder::getBindingMap(void) const
{
    return _bindMap;
}

inline MaterialBinder::BindingMap &
    MaterialBinder::editBindingMap(void)
{
    return _bindMap;
}

#endif // _MATERIALBINDER_H_
