
#ifndef _MATERIALMANAGER_H_
#define _MATERIALMANAGER_H_

#include <Descriptors.h>
//#include <OpenSGVectorInput.h>

#include <map>
#include <iosfwd>
#include <string>
#include <vector>

// VRJuggler includes
#include <vpr/Util/Debug.h>

// OpenSG includes
#include <OpenSG/OSGMaterial.h>
#include <OpenSG/OSGSHLChunk.h>
// #include <OpenSG/OSGShaderParameterVec4f.h>
// #include <OpenSG/OSGShaderParameterReal.h>

// boost includes
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>


// forward declarations
class ShaderManager;
class TextureManager;

class MaterialManager
{
  public:
    typedef std::map<std::string, MaterialDesc>        MaterialMap;   
    typedef std::map<std::string, OSG::MaterialRefPtr> MaterialCacheMap;
  
    typedef MaterialDesc::ShaderParamStore             ShaderParamStore;
    typedef MaterialDesc::ShaderParamStoreIt           ShaderParamStoreIt;
    typedef MaterialDesc::ShaderParamStoreConstIt      ShaderParamStoreConstIt;
    
    typedef std::vector<OSG::SHLChunkRefPtr>           SHLChunkStore;

    MaterialManager(ShaderManager  *pShaderManager,
                    TextureManager *pTextureManager);
    
    /*=======================================================================*/
    /* Materials                                                             */
    /*=======================================================================*/
  
    MaterialDesc const *getMaterialDesc(std::string const &name) const;
    OSG::MaterialRefPtr getMaterial    (std::string const &name) const;  
    
    /*=======================================================================*/
    /* Descriptors                                                           */
    /*=======================================================================*/
    
    void addDesc   (MaterialDesc const *pDesc, bool replace = false);
    bool subDesc   (MaterialDesc const *pDesc                      );
    
    void readFile  (std::string const &fileName);
    void refreshCache   (void);
        
    /*=======================================================================*/
    /* Mode Parameter                                                        */
    /*=======================================================================*/
    
    void setModeParam(int mode);
    int  getModeParam(void    );
    
    /*=======================================================================*/
    /* Access                                                                */
    /*=======================================================================*/
    
    void setDynamicParam(const std::string &name,       OSG::Real32  val);
    void setDynamicParam(const std::string &name, const OSG::Vec4f  &val);

    // direct storage access -- avoid using these, if possible
    MaterialMap            &editMatMap(void);
    MaterialMap      const &getMatMap(void) const;
    
    MaterialCacheMap       &editMatCache(void);
    MaterialCacheMap const &getMatCache(void) const;
    
    void dump(std::ostream &os) const;
    
  private:
    OSG::MaterialRefPtr constructMaterial(MaterialDesc const *pDesc) const;
  
    void addUniform     (ShaderParameterDesc const *pDesc,
                         OSG::SHLChunkRefPtr        pSHL  ) const;
    template <class SingleTypeT, class MultiTypeT>
    void addTypedUniform(ShaderParameterDesc const *pDesc,
                         OSG::SHLChunkRefPtr        pSHL  ) const;
    
    GLenum getBlendFactor(std::string const &factor, bool isSourceFactor) const;
    

    void refreshMaterial(MaterialDesc const *pDesc, OSG::MaterialRefPtr pMat);
                         
            MaterialMap        _matMap;
    mutable MaterialCacheMap   _matCache;

            ShaderParamStore   _globalParamStore;
            
        
            ShaderManager     *_pShaderManager;
            TextureManager    *_pTextureManager;
    
    mutable SHLChunkStore      _shlChunks;
};

inline MaterialManager::MaterialMap &
    MaterialManager::editMatMap(void)
{
    return _matMap;
}

inline MaterialManager::MaterialMap const &
    MaterialManager::getMatMap(void) const
{
    return _matMap;
}

inline MaterialManager::MaterialCacheMap &
    MaterialManager::editMatCache(void)
{
    return _matCache;
}

inline MaterialManager::MaterialCacheMap const &
    MaterialManager::getMatCache(void) const
{
    return _matCache;
}

inline void
    MaterialManager::setDynamicParam(const std::string &name, OSG::Real32 val)
{
    SHLChunkStore::iterator shlIt  = _shlChunks.begin();
    SHLChunkStore::iterator shlEnd = _shlChunks.end  ();
    
    for(; shlIt != shlEnd; ++shlIt)
    {
        //OSG::beginEditCP((*shlIt), OSG::ShaderParameterChunk::ParametersFieldMask);
            (*shlIt)->setUniformParameter(name.c_str(), val);
        //OSG::endEditCP  ((*shlIt), OSG::ShaderParameterChunk::ParametersFieldMask);
    }
}

inline void
    MaterialManager::setDynamicParam(
        const std::string &name, const OSG::Vec4f &val)
{
    SHLChunkStore::iterator shlIt  = _shlChunks.begin();
    SHLChunkStore::iterator shlEnd = _shlChunks.end  ();
    
    for(; shlIt != shlEnd; ++shlIt)
    {
        //OSG::beginEditCP((*shlIt), OSG::ShaderParameterChunk::ParametersFieldMask);
            (*shlIt)->setUniformParameter(name.c_str(), val);
        //OSG::endEditCP  ((*shlIt), OSG::ShaderParameterChunk::ParametersFieldMask);
    }
}

template <class SingleTypeT, class MultiTypeT>
inline void
    MaterialManager::addTypedUniform(
        ShaderParameterDesc const *pDesc, OSG::SHLChunkRefPtr pSHL) const
{
    if(!pDesc->_isArray)
    {
        try
        {
            SingleTypeT val =
                boost::lexical_cast<SingleTypeT>(pDesc->_valueString);
        
            vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
                << "MaterialManager::addTypedUniform: "
                << "Setting [" << pDesc->_name << "] to ["
                << val << "].\n"
                << vprDEBUG_FLUSH;
                
            //OSG::beginEditCP(pSHL);
                pSHL->setUniformParameter(pDesc->_name.c_str(), val);
            //OSG::endEditCP(pSHL);
        } 
        catch(boost::bad_lexical_cast &e)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                << "MaterialManager::addTypedUniform: "
                << "Failed to extract value for sparam [" << pDesc->_name
                << "] from [" << pDesc->_valueString << "]: "
                << e.what() << "\n"
                << vprDEBUG_FLUSH;
        }
    }
    else
    {
        typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
    
        MultiTypeT  mval;
        SingleTypeT val;
        
        boost::char_separator<char> sep(";");
        Tokenizer                   tok(pDesc->_valueString, sep);
        Tokenizer::iterator         tokIt  = tok.begin();
        Tokenizer::iterator         tokEnd = tok.end  ();
        
        try
        {
            for(; tokIt != tokEnd; ++tokIt)
            {
                vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                    << "MaterialManager::addTypedUniform: token ["
                    << *tokIt << "]\n"
                    << vprDEBUG_FLUSH;
            
                val = boost::lexical_cast<SingleTypeT>(*tokIt);
                
                mval.push_back(val);
            }
        }
        catch(boost::bad_lexical_cast &e)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                << "MaterialManager::addTypedUniform: "
                << "Failed to extract value for mparam [" << pDesc->_name
                << "] from [" << pDesc->_valueString << "]: "
                << e.what() << "\n"
                << vprDEBUG_FLUSH;
                
            return;
        }
        
        //OSG::beginEditCP(pSHL);
            pSHL->setUniformParameter(pDesc->_name.c_str(), mval);
        //OSG::endEditCP(pSHL);
    }
}

#endif // _MATERIALMANAGER_H_
