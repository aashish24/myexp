
#include <TextureManager.h>

#include <PathHandler.h>

// VRJuggler includes
#include <vpr/Util/Debug.h>

// OpenSG includes
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGImageFileHandler.h>

#include <ostream>

    TextureManager::TextureManager(PathHandler const *pPathHandler)
    
    : _texMap      (),
      _texCache    (),
      _pPathHandler(pPathHandler)
{
    // nothing to do
}

TextureDesc const *
    TextureManager::getTextureDesc(std::string const &name) const
{
    TextureMap::const_iterator tIt = _texMap.find(name);
    
    if(tIt != _texMap.end())
    {
        return &(tIt->second);
    }
    else
    {
        return NULL;
    }
}


OSG::TextureChunkRefPtr
    TextureManager::getTexture(std::string const &name) const
{
    OSG::TextureChunkRefPtr         pTex;
    TextureCacheMap::const_iterator tIt  = _texCache.find(name);
    
    if(tIt != _texCache.end())
    {
        pTex = tIt->second;
    }
    else
    {
        TextureDesc const *pDesc = getTextureDesc(name);
        
        if(pDesc != NULL)
        {
            pTex = constructTexture(pDesc);
            
            _texCache[pDesc->_name] = pTex;
        }
    }
    
    return pTex;
}

void
    TextureManager::addDesc(TextureDesc const *pDesc, bool replace)
{
    TextureMap::iterator tmIt = _texMap.find(pDesc->_name);
    
    if(tmIt != _texMap.end())
    {
        if(replace)
        	tmIt->second = *pDesc;            
    }
    else
    {
        _texMap.insert(TextureMap::value_type(pDesc->_name, *pDesc));
    }
}

bool
    TextureManager::subDesc(TextureDesc const *pDesc)
{
    bool                      retVal = false;
    TextureMap     ::iterator tmIt   = _texMap  .find(pDesc->_name);
    TextureCacheMap::iterator tcIt   = _texCache.find(pDesc->_name);
    
    if(tcIt != _texCache.end())
    {
        retVal = true;
        _texCache.erase(tcIt);
    }
    
    if(tmIt != _texMap.end())
    {
        retVal = true;
        _texMap.erase(tmIt);    
    }
    
    return retVal;
}

OSG::TextureChunkRefPtr
    TextureManager::constructTexture(TextureDesc const *pDesc) const
{
    OSG::TextureChunkRefPtr pTex   (OSG::TextureChunk::create());
    OSG::ImageRefPtr        pTexImg;
    
    std::string fullImgPath;
    
    if(_pPathHandler->findFile(pDesc->_fileName, fullImgPath) == true)
    {
        pTexImg = OSG::ImageFileHandler::the().read(fullImgPath.c_str());
    }
    else
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
            << "TextureManager::constructTexture: "
            << "Could not find file [" << pDesc->_fileName << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(pTexImg != OSG::NullFC)
    {
        OSG::ImagePtr pTexImage = pTexImg.get();
    
        beginEditCP(pTex);
            pTex->setImage(pTexImage);
        endEditCP  (pTex);
    }
    else
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
            << "TextureManager::constructTexture: "
            << "Failed to read file [" << pDesc->_fileName << "] for texture ["
            << pDesc->_name << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    return OSG::TextureChunkRefPtr(pTex.get());
}

void
    TextureManager::dump(std::ostream &os)
{
    TextureMap::const_iterator tIt  = _texMap.begin();
    TextureMap::const_iterator tEnd = _texMap.end  ();
    
    for(; tIt != tEnd; ++tIt)
    {
        os << "Texture '" << tIt->first << "' ";
        tIt->second.dump(os);
        os << "\n";
    }
}

void 
	TextureManager::refreshCache(void)
{
	TextureCacheMap::iterator tIt  = _texCache.begin();
	TextureCacheMap::iterator tEnd = _texCache.end  ();
    
    for(; tIt != tEnd; ++tIt)
    {
    	TextureDesc const * pDesc = getTextureDesc(tIt->first);
    	OSG::TextureChunkRefPtr  pTex = tIt->second;
    	refreshTexture(pDesc, pTex);
    }
}


void
    TextureManager::refreshTexture(TextureDesc const *pDesc, OSG::TextureChunkRefPtr pTex) 
{
    OSG::ImageRefPtr        pTexImg;
    
    std::string fullImgPath;
    
    if(_pPathHandler->findFile(pDesc->_fileName, fullImgPath) == true)
    {
        pTexImg = OSG::ImageFileHandler::the().read(fullImgPath.c_str());
    }
    else
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
            << "TextureManager::refreshTexture: "
            << "Could not find file [" << pDesc->_fileName << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    if(pTexImg != OSG::NullFC)
    {
        OSG::ImagePtr pTexImage = pTexImg.get();
    
        beginEditCP(pTex);
            pTex->setImage(pTexImage);
        endEditCP  (pTex);
    }
    else
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
            << "TextureManager::refreshTexture: "
            << "Failed to read file [" << pDesc->_fileName << "] for texture ["
            << pDesc->_name << "].\n"
            << vprDEBUG_FLUSH;
    }
    
    //return OSG::TextureChunkRefPtr(pTex.get());
}

