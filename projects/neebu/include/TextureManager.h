
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <Descriptors.h>

#include <map>
#include <iosfwd>
#include <string>

// OpenSG includes
#include <OpenSG/OSGTextureChunk.h>

// forward declarations
class PathHandler;


class TextureManager
{
  public:
    typedef std::map<std::string, TextureDesc>              TextureMap;   
    typedef std::map<std::string, OSG::TextureChunkRefPtr>  TextureCacheMap;
    
    explicit TextureManager(PathHandler const *pPathHandler);
    
    /*=======================================================================*/
    /* Textures                                                              */
    /*=======================================================================*/
    
    TextureDesc const *     getTextureDesc(std::string const &name) const;
    OSG::TextureChunkRefPtr getTexture    (std::string const &name) const;
    void refreshCache(void);
    
    /*=======================================================================*/
    /* Descriptors                                                           */
    /*=======================================================================*/
    
    void addDesc(TextureDesc const *pDesc, bool replace = false);
    bool subDesc(TextureDesc const *pDesc                      );
    
    /*=======================================================================*/
    /* Access                                                                */
    /*=======================================================================*/
    
    // direct storage access -- avoid using these, if possible
    TextureMap            &editTexMap(void);
    TextureMap      const &getTexMap(void) const;
    
    TextureCacheMap       &editTexCache(void);
    TextureCacheMap const &getTexCache(void) const;  
    
    void dump(std::ostream &os);
    unsigned int getSize();
    
  private:
    OSG::TextureChunkRefPtr constructTexture(TextureDesc const *pDesc) const;
    void refreshTexture(TextureDesc const *pDesc, OSG::TextureChunkRefPtr pTex);
  
            TextureMap         _texMap;
    mutable TextureCacheMap    _texCache;
    
            PathHandler const *_pPathHandler;
};

inline unsigned int 
	TextureManager::getSize()
{
	return _texMap.size();
}

inline TextureManager::TextureMap &
    TextureManager::editTexMap(void)
{
    return _texMap;
}

inline TextureManager::TextureMap const &
    TextureManager::getTexMap(void) const
{
    return _texMap;
}

inline TextureManager::TextureCacheMap &
    TextureManager::editTexCache(void)
{
    return _texCache;
}

inline TextureManager::TextureCacheMap const &
    TextureManager::getTexCache(void) const
{
    return _texCache;
}


#endif // _TEXTUREMANAGER_H_
