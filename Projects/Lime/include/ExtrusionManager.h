
#ifndef _EXTRUSIONMANAGER_H_
#define _EXTRUSIONMANAGER_H_

#include <Descriptors.h>

// OpenSG includes
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGVector.h>

// std library includes
#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// forward declarations
class PathHandler;
class NamedObjectCache;


class ExtrusionManager
{
  public:
    typedef ExtrusionManager                     Self;
    
    typedef std::map<std::string, ExtrusionDesc> ExtrusionMap;
    typedef ExtrusionMap::iterator               ExtrusionMapIt;
    typedef ExtrusionMap::const_iterator         ExtrusionMapConstIt;
    
    explicit ExtrusionManager(void);

    void readFile(std::string const &fileName);
    
    void                    setObjCache(NamedObjectCache const *pObjCache);
    NamedObjectCache const *getObjCache(void                             ) const;
    
    void apply(void);
    void update(void);
    
    
    ExtrusionMap const &getExtMap (void) const;
    ExtrusionMap       &editExtMap(void);
        
    void dump(std::ostream &os) const;
        
  private:
  
    struct ExtrusionInfo
    {
        typedef std::vector<OSG::TransformRefPtr> TransformStore;
    
        OSG::GeometryRefPtr _pGeo;
        TransformStore      _cpMeshTrans;
        TransformStore      _cpNodeTrans;
        TransformStore      _cpBBoxTrans;
    };
  
    typedef std::map<std::string, ExtrusionInfo> InfoMap;
    typedef InfoMap::iterator                    InfoMapIt;
    typedef InfoMap::const_iterator              InfoMapConstIt;
  
    void constructGeo  (ExtrusionDesc const &desc, ExtrusionInfo &info);
    void updateVertices(ExtrusionDesc const &desc, ExtrusionInfo &info);
  
    void evalCrossSection(ExtrusionDesc const           &desc,
                          std::vector<OSG::Pnt2f>       &pos,
                          std::vector<OSG::Vec2f>       &tang);
    void evalSpine       (std::vector<OSG::Pnt3f> const &cp, 
                          OSG::Real32                    t,
                          OSG::Pnt3f                    &pos,
                          OSG::Vec3f                    &tang);
    
    template <class DataTypeT, class StorageTypeT>
    void evalBezier(
        OSG::PointInterface <DataTypeT, StorageTypeT>       *pPos,
        OSG::VectorInterface<DataTypeT, StorageTypeT>       *pTang,
        DataTypeT const                                     *pT,
        OSG::UInt32 const                                    numT,
        OSG::PointInterface <DataTypeT, StorageTypeT> const *pCP,
        OSG::UInt32 const                                    order,
        OSG::PointInterface <DataTypeT, StorageTypeT>       *pScratch);
    
  
    NamedObjectCache const *_pObjCache;
    
    ExtrusionMap            _extMap;
    InfoMap                 _infoMap;
};

inline void
    ExtrusionManager::setObjCache(NamedObjectCache const *pObjCache)
{
    _pObjCache = pObjCache;
}

inline NamedObjectCache const *
    ExtrusionManager::getObjCache(void) const
{
    return _pObjCache;
}

inline ExtrusionManager::ExtrusionMap const &
    ExtrusionManager::getExtMap(void) const
{
    return _extMap;
}

inline ExtrusionManager::ExtrusionMap &
    ExtrusionManager::editExtMap(void)
{
    return _extMap;
}

template <class DataTypeT, class StorageTypeT>
inline void
    ExtrusionManager::evalBezier(
        OSG::PointInterface <DataTypeT, StorageTypeT>       *pPos,
        OSG::VectorInterface<DataTypeT, StorageTypeT>       *pTang,
        DataTypeT const                                     *pT,
        OSG::UInt32 const                                    numT,
        OSG::PointInterface <DataTypeT, StorageTypeT> const *pCP,
        OSG::UInt32 const                                    order,
        OSG::PointInterface <DataTypeT, StorageTypeT>       *pScratch)
{
    for(OSG::UInt32 i = 0; i < numT; ++i)
    {
        DataTypeT t0 = pT[i];
        DataTypeT t1 = 1.0 - t0;
        
        // init scratch area
        for(OSG::UInt32 j = 0; j < order; ++j)
            pScratch[j] = pCP[j];
            
        // perform deCasteljau
        for(OSG::UInt32 j = 1; j < order - 1; ++j)
        {
            for(OSG::UInt32 k = 0; k < order - j; ++k)
            {
                pScratch[k] =  t1 * pScratch[k  ];
                pScratch[k] += t0 * pScratch[k+1];
            }
        }
        
        // store tangent
        pTang[i] =  pScratch[1];
        pTang[i] -= pScratch[0];
        pTang[i].normalize();
        
        // store position
        pPos[i] =  t1 * pScratch[0];
        pPos[i] += t0 * pScratch[1];
    }
}

#endif // _EXTRUSIONMANAGER_H_
