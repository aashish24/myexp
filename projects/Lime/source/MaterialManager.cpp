// std library includes
#include <ostream>

#include <MaterialManager.h>

#include <MaterialParser.h>
#include <ShaderManager.h>
#include <TextureManager.h>

// OpenSG includes
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGMaterialFields.h>

// boost includes
#include <boost/spirit/iterator/file_iterator.hpp>



namespace bs = boost::spirit;


    MaterialManager::MaterialManager(
        ShaderManager  *pShaderManager,
        TextureManager *pTextureManager)
        
    : _matMap          (),
      _matCache        (),
      _globalParamStore(),
      _pShaderManager  (pShaderManager ),
      _pTextureManager (pTextureManager)
{
}

MaterialDesc const *
    MaterialManager::getMaterialDesc(std::string const &name) const
{
    MaterialMap::const_iterator mIt = _matMap.find(name);
    
    if(mIt != _matMap.end())
    {
        return &(mIt->second);
    }
    else
    {
        return NULL;
    }
}

OSG::MaterialRefPtr
    MaterialManager::getMaterial(std::string const &name) const
{
    OSG::MaterialRefPtr              pMat;
    MaterialCacheMap::const_iterator mIt  = _matCache.find(name);
    
    if(mIt != _matCache.end())
    {
        pMat = mIt->second;
    }
    else
    {
        MaterialDesc const *pDesc = getMaterialDesc(name);
        
        if(pDesc != NULL)
        {
            pMat = constructMaterial(pDesc);
            
            _matCache[pDesc->_name] = pMat;
        }
    }
    
    return pMat;
}

void
    MaterialManager::addDesc(MaterialDesc const *pDesc, bool replace)
{
    MaterialMap::iterator mmIt = _matMap.find(pDesc->_name);
      
    if(mmIt != _matMap.end())
    { 	
        if(replace)
        	mmIt->second = *pDesc;
    }
    else
    {
        _matMap.insert(MaterialMap::value_type(pDesc->_name, *pDesc));
    }
}

bool
    MaterialManager::subDesc(MaterialDesc const *pDesc)
{
    bool                       retVal = false;
    MaterialMap     ::iterator mmIt   = _matMap  .find(pDesc->_name);
    MaterialCacheMap::iterator mcIt   = _matCache.find(pDesc->_name);
    
    if(mcIt != _matCache.end())
    {
        retVal = true;
        _matCache.erase(mcIt);
    }
    
    if(mmIt != _matMap.end())
    {
        retVal = true;
        _matMap.erase(mmIt);    
    }
    
    return retVal;
}


void
    MaterialManager::readFile(std::string const &fileName)
{
    typedef char                         char_t;
    typedef bs::file_iterator<char_t>    FileItType;
    
    typedef MaterialBuilder<FileItType>  MatBuilder;
    typedef MaterialGrammar<MatBuilder>  MatGrammar;
    
    MatBuilder matBuilder;
    MatGrammar matGrammar(&matBuilder);
    
    FileItType fileIt(fileName);
        
    if(!fileIt)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL) 
            << "MaterialManager::readFile: Could not open material file "
            << "'" << fileName << "'."
            << std::endl << vprDEBUG_FLUSH;
            
        return;
    }
    
    FileItType fileEnd = fileIt.make_end();
    
    bs::parse_info<FileItType> info = 
        parse(fileIt, fileEnd, matGrammar >> bs::eps_p, bs::space_p);
        
    if(!info.hit)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "MaterialManager::readFile: Parsing of material file "
            << "'" << fileName << "' failed.\n"
            << vprDEBUG_FLUSH;
            
            return;
    }
    
    MatBuilder::ShaderParamStoreConstIt spIt  = matBuilder.getGlobalParams().begin();
    MatBuilder::ShaderParamStoreConstIt spEnd = matBuilder.getGlobalParams().end  ();
    
    for(; spIt != spEnd; ++spIt)
    {
    	ShaderParamStoreIt globparam;
    	std::string tname = (*spIt)._name;
    	    	
    	globparam = std::find_if(_globalParamStore.begin(), _globalParamStore.end(), hasThisName(tname) );
    	if (globparam == _globalParamStore.end())
    		_globalParamStore.push_back(*spIt);
    	else
    		(*globparam) = (*spIt);
    }
    
    MatBuilder::MaterialDescStoreConstIt matIt  = matBuilder.getMatStore().begin();
    MatBuilder::MaterialDescStoreConstIt matEnd = matBuilder.getMatStore().end  ();
    
    for(; matIt != matEnd; ++matIt)
    {
        addDesc(&(*matIt), true);
    }
    
    MatBuilder::TextureDescStoreConstIt texIt  = matBuilder.getTexStore().begin();
    MatBuilder::TextureDescStoreConstIt texEnd = matBuilder.getTexStore().end  ();
    
    for(; texIt != texEnd; ++texIt)
    {
        _pTextureManager->addDesc(&(*texIt), true);
    }
    
    MatBuilder::ShaderProgramDescStoreConstIt sIt  = matBuilder.getShaderProgStore().begin();
    MatBuilder::ShaderProgramDescStoreConstIt sEnd = matBuilder.getShaderProgStore().end  ();
    
    for(; sIt != sEnd; ++sIt)
    {
        _pShaderManager->addDesc(&(*sIt), true);
    }
    
    vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
        << "MaterialManager::readFile: After parsing of material file "
        << "'" << fileName << "':\n" 
        << _globalParamStore.size() << " global params, " 
        << _matMap.size() << " materials, "
        << _pTextureManager->getSize() << " textures, " 
        << _pShaderManager->getVPmapsize() << " VPs, "
        << _pShaderManager->getFPmapsize() << " FPs\n "
        << vprDEBUG_FLUSH;    
}

OSG::MaterialRefPtr
    MaterialManager::constructMaterial(MaterialDesc const *pDesc) const
{
    vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
        << "MaterialManager::constructMaterial:\n"
        << vprDEBUG_FLUSH;

    OSG::ChunkMaterialRefPtr pChunkMat(OSG::ChunkMaterial::create());
    OSG::SHLChunkRefPtr      pSHL     (OSG::SHLChunk     ::create());
    
    std::string const *pVProg = _pShaderManager->getVertexProg  (pDesc->_vpName);
    std::string const *pFProg = _pShaderManager->getFragmentProg(pDesc->_fpName);
    
    if((pVProg != NULL) && (pFProg != NULL))
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            <<  " adding vp [" << pDesc->_vpName
            << "] adding fp [" << pDesc->_fpName
            << "]\n"
            << vprDEBUG_FLUSH;
    
        //OSG::beginEditCP(pSHL);
            pSHL->setVertexProgram  (*pVProg);
            pSHL->setFragmentProgram(*pFProg);
            
//             pSHL->setUnknownParameterWarning(false);
        // OSG::endEditCP(pSHL);
    }
    
    // add textures
    std::size_t numTex = pDesc->_texNames.size();
    
    for(std::size_t i = 0; i < numTex; ++i)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "Adding texture [" << i << "] [" << pDesc->_texNames[i] << "]\n"
            << vprDEBUG_FLUSH;
    
        OSG::TextureChunkRefPtr pTex(
            _pTextureManager->getTexture(pDesc->_texNames[i]));
                    
        if(!pTex)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                << "MaterialManager::constructMaterial: Failed to obtain "
                << "texture [" << pDesc->_texNames[i] << "].\n"
                << vprDEBUG_FLUSH;
            continue;
        }
               
        //OSG:://OSG::beginEditCP(pChunkMat);
            pChunkMat->addChunk(pTex, pDesc->_texSlots[i]);
       // OSG::// OSG::endEditCP  (pChunkMat);
                
        //OSG:://OSG::beginEditCP(pSHL);
            pSHL->setUniformParameter(pDesc->_texSamplerNames[i].c_str(),
                                      pDesc->_texSlots[i]                );
       // OSG::// OSG::endEditCP  (pSHL);
    }
    
    // add the "magic" parameters
    
    //OSG:://OSG::beginEditCP(pSHL);
        pSHL->setUniformParameter("keyColor",       OSG::Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
        pSHL->setUniformParameter("antiColor",      OSG::Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
        pSHL->setUniformParameter("fogNearColor",   OSG::Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
        pSHL->setUniformParameter("fogFarColor",    OSG::Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
        pSHL->setUniformParameter("fogNear",        OSG::Real32(0.0)                  );
        pSHL->setUniformParameter("fogFar",         OSG::Real32(0.0)                  );
        pSHL->setUniformParameter("gSpec",          OSG::Real32(0.0)                  );
        pSHL->setUniformParameter("animTime",       OSG::Real32(0.0)                  );
        pSHL->setUniformParameter("frameTime",      OSG::Real32(0.0)                  );
        pSHL->setUniformParameter("deltaFrameTime", OSG::Real32(0.0)                  );
   // OSG::// OSG::endEditCP  (pSHL);

    _shlChunks.push_back(pSHL);
    
    // add global shader parameters
    std::size_t numGlobalParams = _globalParamStore.size();
    
    for(std::size_t i = 0; i < numGlobalParams; ++i)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "Adding global uniform parameter [" << _globalParamStore[i]._name
            << "].\n"
            << vprDEBUG_FLUSH;
            
        addUniform(&_globalParamStore[i], pSHL);
    }

    // add shader parameters
    std::size_t numParams = pDesc->_shaderParams.size();
    
    for(std::size_t i = 0; i < numParams; ++i)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "Adding uniform parameter [" << pDesc->_shaderParams[i]._name
            << "].\n"
            << vprDEBUG_FLUSH;
    
        addUniform(&(pDesc->_shaderParams[i]), pSHL);
    }
    
    // store SHL chunk in material
    //OSG:://OSG::beginEditCP(pChunkMat);
        pChunkMat->addChunk(pSHL);
   // OSG::// OSG::endEditCP  (pChunkMat);
    
    // add face culling settings
    if(pDesc->_cullFace != "none")
    {
        bool                    addChunk = false;
        OSG::PolygonChunkRefPtr pPoly   (OSG::PolygonChunk::create());
        
        //OSG:://OSG::beginEditCP(pPoly);
            if(pDesc->_cullFace == "front")
            {
                pPoly->setCullFace(GL_FRONT);
                addChunk = true;
            }   
            else if(pDesc->_cullFace == "back")
            {
                pPoly->setCullFace(GL_BACK);
                addChunk = true;
            }   
            else if(pDesc->_cullFace == "both")
            {
                pPoly->setCullFace(GL_FRONT_AND_BACK);
                addChunk = true;
            }
       // OSG::// OSG::endEditCP  (pPoly);
        
        if(addChunk)
        {
            //OSG:://OSG::beginEditCP(pChunkMat);
                pChunkMat->addChunk(pPoly);
           // OSG::// OSG::endEditCP  (pChunkMat);
        }
    }
    
    // add blending settings
    if(pDesc->_blendSource != "" || pDesc->_blendDest != "")
    {
        OSG::BlendChunkRefPtr pBlend(OSG::BlendChunk::create());
        
        //OSG:://OSG::beginEditCP(pBlend);
            pBlend->setSrcFactor (getBlendFactor(pDesc->_blendSource, true ));
            pBlend->setDestFactor(getBlendFactor(pDesc->_blendDest,   false));
       // OSG::// OSG::endEditCP  (pBlend);
        
        //OSG:://OSG::beginEditCP(pChunkMat);
            pChunkMat->addChunk(pBlend);
       // OSG::// OSG::endEditCP  (pChunkMat);
    }
    
    
    return OSG::MaterialRefPtr(pChunkMat.get());
}

void
    MaterialManager::addUniform(
        ShaderParameterDesc const *pDesc, OSG::SHLChunkRefPtr pSHL) const
{
    if(pDesc->_type == "bool")
    {
        addTypedUniform<OSG::Int32, OSG::MFInt32>(pDesc, pSHL);
        return;
    }
    
    if(pDesc->_type == "int")
    {
        addTypedUniform<OSG::Int32, OSG::MFInt32>(pDesc, pSHL);
        return;
    }
    
    if(pDesc->_type == "float")
    {
        addTypedUniform<OSG::Real32, OSG::MFReal32>(pDesc, pSHL);
        return;
    }
    
    if(pDesc->_type == "vec2")
    {   
        addTypedUniform<OSG::Vec2f, OSG::MFVec2f>(pDesc, pSHL);
        return;
    }
    
    if(pDesc->_type == "vec3")
    {
        addTypedUniform<OSG::Vec3f, OSG::MFVec3f>(pDesc, pSHL);
        return;
    }
    
    if(pDesc->_type == "vec4")
    {
        addTypedUniform<OSG::Vec4f, OSG::MFVec4f>(pDesc, pSHL);
        return;
    }
}

GLenum
    MaterialManager::getBlendFactor(
        std::string const &factor, bool isSourceFactor) const
{
    if(factor == "zero")
        return GL_ZERO;
        
    if(factor == "one")
        return GL_ONE;
        
    if(factor == "src_alpha")
        return GL_SRC_ALPHA;
        
    if(factor == "one_minus_src_alpha")
        return GL_ONE_MINUS_SRC_ALPHA;
        
    if(factor == "" && isSourceFactor)
        return GL_ONE;
        
    if(factor == "" && !isSourceFactor)
        return GL_ZERO;
        
    vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
        << "MaterialManager::getBlendFactor: Unrecognized value ["
        << factor << "].\n"
        << vprDEBUG_FLUSH;
        
    return GL_NONE;
}

void
    MaterialManager::dump(std::ostream &os) const
{
    MaterialMap::const_iterator mIt  = _matMap.begin();
    MaterialMap::const_iterator mEnd = _matMap.end  ();
    
    for(; mIt != mEnd; ++mIt)
    {
        os << "Material '" << mIt->first << "' ";
        mIt->second.dump(os);
        os << "\n";
    }
}


void
	MaterialManager::refreshCache(void)
{
	_pTextureManager->refreshCache();
	
    OSG::MaterialRefPtr        pMat;     
    MaterialCacheMap::iterator mIt;   
    
    for(mIt = _matCache.begin(); mIt != _matCache.end(); mIt++){
    	MaterialDesc const *pDesc = getMaterialDesc(mIt->first);
    	pMat  = mIt->second;
    	refreshMaterial(pDesc,pMat);    	
    }  
}

void
    MaterialManager::refreshMaterial(MaterialDesc const *pDesc, OSG::MaterialRefPtr pMat)
{	
	
  OSG::ChunkMaterialRefPtr pChunkMat (OSG::dynamic_pointer_cast<OSG::ChunkMaterial>(pMat));	
	OSG::SHLChunkRefPtr      pSHL      (dynamic_cast<OSG::SHLChunk *>(pChunkMat->find(OSG::SHLChunk::getClassType())));
	
    std::string const *pVProg = _pShaderManager->getVertexProg  (pDesc->_vpName);
    std::string const *pFProg = _pShaderManager->getFragmentProg(pDesc->_fpName);
    
    if((pVProg != NULL) && (pFProg != NULL))
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            <<  "MaterialManager::refreshMaterial : adding vp [" << pDesc->_vpName
            << "] adding fp [" << pDesc->_fpName
            << "]\n"
            << vprDEBUG_FLUSH;
    
        //OSG::beginEditCP(pSHL);
            pSHL->setVertexProgram  (*pVProg);
            pSHL->setFragmentProgram(*pFProg);
        // OSG::endEditCP(pSHL);
    }
    else 
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            <<  "MaterialManager::refreshMaterial : setting vp and fp to NULL" << std::endl
            << vprDEBUG_FLUSH;
     	
        //OSG::beginEditCP(pSHL);
            pSHL->setVertexProgram  (NULL);
            pSHL->setFragmentProgram(NULL);
        // OSG::endEditCP(pSHL);    	
    }
    

    //TODO
    //delete texture chunks if not used anymore 
    
    // add textures
    std::size_t numTex = pDesc->_texNames.size();    
    for(std::size_t i = 0; i < numTex; ++i)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MaterialManager::refreshMaterial : Adding texture [" << i << "] [" << pDesc->_texNames[i] << "]\n"
            << vprDEBUG_FLUSH;
    
        OSG::TextureChunkRefPtr pTex(_pTextureManager->getTexture(pDesc->_texNames[i]));
        pTex = _pTextureManager->getTexture(pDesc->_texNames[i]);
                    
        if(!pTex)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                << "MaterialManager::refreshMaterial : Failed to obtain "
                << "texture [" << pDesc->_texNames[i] << "].\n"
                << vprDEBUG_FLUSH;
            continue;
        }
               
        //OSG:://OSG::beginEditCP(pChunkMat);
            pChunkMat->addChunk(pTex, pDesc->_texSlots[i]);
       // OSG::// OSG::endEditCP  (pChunkMat);
                
        //TODO
        //delete unused uniform parameters
        //OSG:://OSG::beginEditCP(pSHL);
            pSHL->setUniformParameter(pDesc->_texSamplerNames[i].c_str(),
                                      pDesc->_texSlots[i]                );
       // OSG::// OSG::endEditCP  (pSHL);     
        
    }
    
    // add global shader parameters
    std::size_t numGlobalParams = _globalParamStore.size();
    
    for(std::size_t i = 0; i < numGlobalParams; ++i)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MaterialManager::refreshMaterial : Adding global uniform parameter [" << _globalParamStore[i]._name
            << "].\n"
            << vprDEBUG_FLUSH;
            
        addUniform(&_globalParamStore[i], pSHL);
        //TODO
        //delete unused uniforms
    }
    
    // add the "magic" parameters
    /*
    //OSG:://OSG::beginEditCP(pSHL);
        pSHL->getParameters().push_back(_pKeyColorParam );
        pSHL->getParameters().push_back(_pAntiColorParam);
        pSHL->getParameters().push_back(_pFogColorParam );
        pSHL->getParameters().push_back(_pFogNearParam  );
        pSHL->getParameters().push_back(_pFogFarParam   );
        pSHL->getParameters().push_back(_pSpecParam     );
   // OSG::// OSG::endEditCP  (pSHL);
	*/
    //_shlChunks.push_back(pSHL);

    // add shader parameters
    std::size_t numParams = pDesc->_shaderParams.size();
    
    for(std::size_t i = 0; i < numParams; ++i)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
            << "MaterialManager::refreshMaterial : Adding uniform parameter [" << pDesc->_shaderParams[i]._name
            << "].\n"
            << vprDEBUG_FLUSH;
    
        addUniform(&(pDesc->_shaderParams[i]), pSHL);
        //TODO
        //delete unused uniforms
    }
    
   
    // face culling settings
    bool                    addChunk;
    bool                    editChunk = false;       
    OSG::PolygonChunkRefPtr pPoly (dynamic_cast<OSG::PolygonChunk *>(pChunkMat->find(OSG::PolygonChunk::getClassType())));
    
    if (!pPoly){
    	pPoly = OSG::PolygonChunk::create();
    	addChunk = true;
    }
    else
    	addChunk = false;
    
    //OSG:://OSG::beginEditCP(pPoly);
        if(pDesc->_cullFace == "front")
        {
            pPoly->setCullFace(GL_FRONT);
            editChunk = true;
        }   
        else if(pDesc->_cullFace == "back")
        {
            pPoly->setCullFace(GL_BACK);
            editChunk = true;
        }   
        else if(pDesc->_cullFace == "both")
        {
            pPoly->setCullFace(GL_FRONT_AND_BACK);
            editChunk = true;
        }
   // OSG::// OSG::endEditCP  (pPoly);
    
    if( addChunk && editChunk )
    {
        //OSG:://OSG::beginEditCP(pChunkMat);
            pChunkMat->addChunk(pPoly);
       // OSG::// OSG::endEditCP  (pChunkMat);
    }
    else if ( !addChunk && !editChunk ){
        //OSG:://OSG::beginEditCP(pChunkMat);
            pChunkMat->subChunk(pPoly);
       // OSG::// OSG::endEditCP  (pChunkMat);
    }

    
    //blending settings
    OSG::BlendChunkRefPtr pBlend(dynamic_cast<OSG::BlendChunk *>(pChunkMat->find(OSG::BlendChunk::getClassType())));
    
    if(pDesc->_blendSource != "" || pDesc->_blendDest != "")
    {
    	if (!pBlend){
    		pBlend = OSG::BlendChunk::create();
            //OSG:://OSG::beginEditCP(pChunkMat);
                pChunkMat->addChunk(pBlend);
           // OSG::// OSG::endEditCP  (pChunkMat);    		
    	}
    	
        //OSG:://OSG::beginEditCP(pBlend);
            pBlend->setSrcFactor (getBlendFactor(pDesc->_blendSource, true ));
            pBlend->setDestFactor(getBlendFactor(pDesc->_blendDest,   false));
       // OSG::// OSG::endEditCP  (pBlend);
        
     }
    else if (pBlend){ //delete blending setting if not used
        //OSG:://OSG::beginEditCP(pChunkMat);
            pChunkMat->subChunk(pBlend);
       // OSG::// OSG::endEditCP  (pChunkMat);
    	
    }
    
    
}
