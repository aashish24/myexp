
#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

#include <Descriptors.h>

#include <map>
#include <iosfwd>
#include <string>

// forward declarations
class PathHandler;


class ShaderManager
{
  public:
    typedef std::map<std::string, ShaderProgramDesc> ProgramMap;
    typedef std::map<std::string, std::string      > ProgramCacheMap;

    explicit ShaderManager(PathHandler const *pPathHandler);
    
    /*=======================================================================*/
    /* Shaders                                                               */
    /*=======================================================================*/
    
    ShaderProgramDesc const *getVertexProgDesc  (std::string const &name) const;
    std::string       const *getVertexProg      (std::string const &name) const;
    
    ShaderProgramDesc const *getFragmentProgDesc(std::string const &name) const;
    std::string       const *getFragmentProg    (std::string const &name) const;

    /*=======================================================================*/
    /* Descriptors                                                           */
    /*=======================================================================*/
    
    void addDesc(ShaderProgramDesc const *pDesc, bool replace = false);
    bool subDesc(ShaderProgramDesc const *pDesc                      );    
    
    /*=======================================================================*/
    /* Access                                                                */
    /*=======================================================================*/
    
    // direct storage access -- avoid using these, if possible
    ProgramMap            &editVPMap  (void);
    ProgramMap      const &getVPMap   (void) const;
    
    ProgramCacheMap       &editVPCache(void);
    ProgramCacheMap const &getVPCache (void) const;
    
    ProgramMap            &editFPMap  (void);
    ProgramMap      const &getFPMap   (void) const;
    
    ProgramCacheMap       &editFPCache(void);
    ProgramCacheMap const &getFPCache (void) const;
    
    void dump(std::ostream &os);
    
    unsigned int getVPmapsize(void) const;
    unsigned int getFPmapsize(void) const;
    
  private:
    bool constructProg(ShaderProgramDesc const *pDesc,
                       std::string             &progString) const;
  
            ProgramMap         _vertexProgMap;
    mutable ProgramCacheMap    _vertexProgCache;
    
            ProgramMap         _fragmentProgMap;
    mutable ProgramCacheMap    _fragmentProgCache;
    
            PathHandler const *_pPathHandler;
};

inline unsigned int ShaderManager::getVPmapsize() const
{
	return _vertexProgMap.size();	
}

inline unsigned int ShaderManager::getFPmapsize() const
{
	return _fragmentProgMap.size();
}

inline ShaderManager::ProgramMap &
    ShaderManager::editVPMap(void)
{
    return _vertexProgMap;
}

inline ShaderManager::ProgramMap const &
    ShaderManager::getVPMap(void) const
{
    return _vertexProgMap;
}

inline ShaderManager::ProgramCacheMap &
    ShaderManager::editVPCache(void)
{
    return _vertexProgCache;
}

inline ShaderManager::ProgramCacheMap const &
    ShaderManager::getVPCache(void) const
{
    return _vertexProgCache;
}

inline ShaderManager::ProgramMap &
    ShaderManager::editFPMap(void)
{
    return _fragmentProgMap;
}

inline ShaderManager::ProgramMap const &
    ShaderManager::getFPMap(void) const
{
    return _fragmentProgMap;
}

inline ShaderManager::ProgramCacheMap &
    ShaderManager::editFPCache(void)
{
    return _fragmentProgCache;
}

inline ShaderManager::ProgramCacheMap const &
    ShaderManager::getFPCache(void) const
{
    return _fragmentProgCache;
}

#endif // _SHADERMANAGER_H_
