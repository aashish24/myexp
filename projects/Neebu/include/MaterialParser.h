
#ifndef _MATERIALPARSER_H_
#define _MATERIALPARSER_H_

#include <Descriptors.h>

#include <vector>

// boost spirit includes
// #define BOOST_SPIRIT_DEBUG
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/utility/lists.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>

// debug includes
#include <iostream>

namespace bs = boost::spirit;
namespace ba = boost::algorithm;

/*===========================================================================*/
/* MaterialBuilder<IteratorTypeT>                                            */
/*===========================================================================*/

template <class IteratorTypeT>
class MaterialBuilder
{
  public:
    typedef IteratorTypeT                                   IteratorType;
    
    typedef MaterialBuilder<IteratorType>                   Self;
  
    typedef          std::vector<MaterialDesc>              MaterialDescStore;
    typedef typename MaterialDescStore::iterator            MaterialDescStoreIt;
    typedef typename MaterialDescStore::const_iterator      MaterialDescStoreConstIt;
    
    typedef typename MaterialDesc::ShaderParamStore         ShaderParamStore;
    typedef typename MaterialDesc::ShaderParamStoreIt       ShaderParamStoreIt;
    typedef typename MaterialDesc::ShaderParamStoreConstIt  ShaderParamStoreConstIt;
    
    typedef          std::vector<TextureDesc>               TextureDescStore;
    typedef typename TextureDescStore::iterator             TextureDescStoreIt;
    typedef typename TextureDescStore::const_iterator       TextureDescStoreConstIt;
        
    typedef          std::vector<ShaderProgramDesc>         ShaderProgramDescStore;
    typedef typename ShaderProgramDescStore::iterator       ShaderProgramDescStoreIt;
    typedef typename ShaderProgramDescStore::const_iterator ShaderProgramDescStoreConstIt;
    
    
    MaterialBuilder(void);
    
       
    void beginMaterial(IteratorType nameBegin, IteratorType nameEnd);
    void endMaterial  (IteratorType begin,     IteratorType end);
    
    void setCullFace  (IteratorType faceBegin, IteratorType faceEnd);
    
    void setBlendSource(IteratorType factorBegin, IteratorType factorEnd);
    void setBlendDest  (IteratorType factorBegin, IteratorType factorEnd);
    
    void addTexture           (IteratorType begin,     IteratorType end);
    void setTextureId         (unsigned int id);
    void setTextureName       (IteratorType nameBegin, IteratorType nameEnd);
    void setTextureSamplerName(IteratorType nameBegin, IteratorType nameEnd);
    void setTextureSizeX      (unsigned int size);
    void setTextureSizeY      (unsigned int size);
    
    void setFPName(IteratorType nameBegin, IteratorType nameEnd);
    void setVPName(IteratorType nameBegin, IteratorType nameEnd);
    
    void addParam      (IteratorType begin,      IteratorType end);
    void setParamName  (IteratorType nameBegin,  IteratorType nameEnd);
    void setParamValue (IteratorType valueBegin, IteratorType valuEnd);
    void setParamType  (IteratorType typeBegin,  IteratorType typeEnd);
    void setParamArray (IteratorType begin,      IteratorType end);
    
    void beginGlobalParams(IteratorType begin,   IteratorType end);
    void endGlobalParams  (IteratorType begin,   IteratorType end);
    
    void beginTexture  (IteratorType nameBegin, IteratorType nameEnd);
    void setTextureFile(IteratorType nameBegin, IteratorType nameEnd);
    void endTexture    (IteratorType begin,     IteratorType end    );
    
    
    void beginShader  (IteratorType nameBegin, IteratorType nameEnd);
    void setShaderFile(IteratorType nameBegin, IteratorType nameEnd);
    void setShaderType(IteratorType typeBegin, IteratorType typeEnd);
    void endShader    (IteratorType begin,     IteratorType end    );
    
    
    MaterialDescStore             &editMatStore(void);
    MaterialDescStore       const &getMatStore (void) const;
    
    TextureDescStore              &editTexStore(void);
    TextureDescStore       const  &getTexStore (void) const;
    
    ShaderProgramDescStore        &editShaderProgStore(void);
    ShaderProgramDescStore const  &getShaderProgStore (void) const;
    
    ShaderParamStore              &editGlobalParams(void);
    ShaderParamStore const        &getGlobalParams (void);
    
  private:
    bool                    _inGlobals;
  
    MaterialDescStore       _matStore;
    TextureDescStore        _texStore;
    ShaderProgramDescStore  _shaderStore;
    
    ShaderParamStore        _globalParamStore;
};

template <class IteratorTypeT>
inline
    MaterialBuilder<IteratorTypeT>::MaterialBuilder(void)
    
    : _inGlobals(false),
      _matStore(),
      _texStore(),
      _globalParamStore()
{
    // nothing to do
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::beginMaterial(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string matName(nameBegin, nameEnd);

#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "beginMaterial: " << matName << std::endl;
#endif
    
    _matStore.push_back(MaterialDesc());
    _matStore.back()._name     = matName.substr(1, matName.length() - 2);
    _matStore.back()._cullFace = "none";
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::endMaterial(
        IteratorType begin, IteratorType end)
{
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "endMaterial: " << std::endl;
#endif
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setCullFace(
        IteratorType faceBegin, IteratorType faceEnd)
{
    std::string cullFace(faceBegin, faceEnd);

#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setCullFace: " << cullFace << std::endl;
#endif
    
    _matStore.back()._cullFace = cullFace;
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setBlendSource(
        IteratorType factorBegin, IteratorType factorEnd)
{
    std::string factor(factorBegin, factorEnd);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setBlendSource: " << factor << std::endl;
#endif
    
    _matStore.back()._blendSource = factor;
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setBlendDest  (
        IteratorType factorBegin, IteratorType factorEnd)
{
    std::string factor(factorBegin, factorEnd);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setBlendDest: " << factor << std::endl;
#endif
    
    _matStore.back()._blendDest = factor;
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::addTexture(
        IteratorType begin, IteratorType end)
{
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "addTexture: " << std::endl;
#endif
    
    _matStore.back()._texNames       .push_back("");
    _matStore.back()._texSamplerNames.push_back("");
    _matStore.back()._texSlots       .push_back(-1);
    _matStore.back()._texSizesX      .push_back(-1);
    _matStore.back()._texSizesY      .push_back(-1);
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setTextureId(unsigned int id)
{   
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setTextureId: " << id << std::endl;
#endif
    
    _matStore.back()._texSlots.back() = id;
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setTextureName(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string texName(nameBegin, nameEnd);

#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setTextureName: " << texName << std::endl;
#endif
    
    _matStore.back()._texNames.back() = texName.substr(1, texName.length() - 2);
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setTextureSamplerName(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string texSampler(nameBegin, nameEnd);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setTextureSamplerName: " << texSampler << std::endl;
#endif
    
    _matStore.back()._texSamplerNames.back() =
        texSampler.substr(1, texSampler.length() - 2);
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setTextureSizeX(unsigned int size)
{
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setTextureSizeX: " << size << std::endl;
#endif

    _matStore.back()._texSizesX.back() = size;
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setTextureSizeY(unsigned int size)
{
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setTextureSizeY: " << size << std::endl;
#endif

    _matStore.back()._texSizesY.back() = size;
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setFPName(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string fpName(nameBegin, nameEnd);

#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setFPName: " << fpName << std::endl;
#endif
    
    _matStore.back()._fpName = fpName.substr(1, fpName.length() - 2);
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setVPName(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string vpName(nameBegin, nameEnd);

#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setVPName: " << vpName << std::endl;
#endif
    
    _matStore.back()._vpName = vpName.substr(1, vpName.length() - 2);
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::addParam(
        IteratorType begin, IteratorType end)
{
    if(_inGlobals == true)
    {
        _globalParamStore.push_back(ShaderParameterDesc());
        _globalParamStore.back()._isArray = false;
        
#ifdef BOOST_SPIRIT_DEBUG
        std::cerr << "addParam: (global)" << std::endl;
#endif
    }
    else
    {
        _matStore.back()._shaderParams.push_back(ShaderParameterDesc());
        _matStore.back()._shaderParams.back()._isArray = false;
        
#ifdef BOOST_SPIRIT_DEBUG
        std::cerr << "addParam: " << std::endl;
#endif
    }
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setParamName(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string paramName(nameBegin, nameEnd);

    if(_inGlobals == true)
    {
        _globalParamStore.back()._name = paramName;
    }
    else
    {    
        _matStore.back()._shaderParams.back()._name = paramName;
    }
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setParamName: " << paramName << std::endl;
#endif
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setParamValue(
        IteratorTypeT valueBegin, IteratorTypeT valueEnd)
{
    std::string paramValue(valueBegin, valueEnd);
    ba::trim_if(paramValue, ba::is_any_of("{} "));

    if(_inGlobals == true)
    {
        _globalParamStore.back()._valueString = paramValue;
    }
    else
    {
        _matStore.back()._shaderParams.back()._valueString = paramValue;
    }
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setParamValue: " << paramValue << std::endl;
#endif
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setParamType(
        IteratorType typeBegin, IteratorType typeEnd)
{
    std::string paramType(typeBegin, typeEnd);
    
    if(_inGlobals == true)
    {
        _globalParamStore.back()._type = paramType;
    }
    else
    {
        _matStore.back()._shaderParams.back()._type = paramType;
    }

#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setParamType: " << paramType << std::endl;
#endif
}

template <class IteratorTypeT>
inline void 
    MaterialBuilder<IteratorTypeT>::setParamArray(
        IteratorType begin, IteratorType end)
{
    if(_inGlobals == true)
    {
        _globalParamStore.back()._isArray = true;
    }
    else
    {
        _matStore.back()._shaderParams.back()._isArray = true;
    }
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setParamArray: " << std::endl;
#endif
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::beginGlobalParams(
        IteratorType begin, IteratorType end)
{
    _inGlobals = true;
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "beginGlobalParams: " << std::endl;
#endif
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::endGlobalParams(
        IteratorType begin, IteratorType end)
{
    _inGlobals = false;
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "endGlobalParams: " << std::endl;
#endif
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::beginTexture(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string texName(nameBegin, nameEnd);

#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "beginTexture: " << texName << std::endl;
#endif
    
    _texStore.push_back(TextureDesc());
    _texStore.back()._name = texName.substr(1, texName.length() - 2);
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setTextureFile(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string fileName(nameBegin, nameEnd);

#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setTextureFile: " << fileName << std::endl;
#endif
    
    _texStore.back()._fileName = fileName.substr(1, fileName.length() - 2);
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::endTexture(
        IteratorType begin, IteratorType end)
{
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "endTexture" << std::endl;
#endif
}


template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::beginShader(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string shaderName(nameBegin, nameEnd);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "beginShader: " << shaderName << std::endl;
#endif
    
    _shaderStore.push_back(ShaderProgramDesc());
    _shaderStore.back()._name = shaderName.substr(1, shaderName.length() - 2);
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setShaderFile(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string fileName(nameBegin, nameEnd);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setShaderFile: " << fileName << std::endl;
#endif
    
    _shaderStore.back()._fileName = fileName.substr(1, fileName.length() - 2);
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::setShaderType(
        IteratorType typeBegin, IteratorType typeEnd)
{
    std::string shaderType(typeBegin, typeEnd);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "setShaderType: " << shaderType << std::endl;
#endif
    
    _shaderStore.back()._type = shaderType;
}

template <class IteratorTypeT>
inline void
    MaterialBuilder<IteratorTypeT>::endShader(
        IteratorType begin, IteratorType end)
{
#ifdef BOOST_SPIRIT_DEBUG
    std::cerr << "endShader" << std::endl;
#endif
}

template <class IteratorTypeT>
inline typename MaterialBuilder<IteratorTypeT>::MaterialDescStore &
    MaterialBuilder<IteratorTypeT>::editMatStore(void)
{
    return _matStore;
}

template <class IteratorTypeT>
inline typename MaterialBuilder<IteratorTypeT>::MaterialDescStore const &
    MaterialBuilder<IteratorTypeT>::getMatStore (void) const
{
    return _matStore;
}

template <class IteratorTypeT>
inline typename MaterialBuilder<IteratorTypeT>::TextureDescStore &
    MaterialBuilder<IteratorTypeT>::editTexStore(void)
{
    return _texStore;
}

template <class IteratorTypeT>
inline typename MaterialBuilder<IteratorTypeT>::TextureDescStore const &
    MaterialBuilder<IteratorTypeT>::getTexStore (void) const
{
    return _texStore;
}

template <class IteratorTypeT>
inline typename MaterialBuilder<IteratorTypeT>::ShaderProgramDescStore &
    MaterialBuilder<IteratorTypeT>::editShaderProgStore(void)
{
    return _shaderStore;
}

template <class IteratorTypeT>
inline typename MaterialBuilder<IteratorTypeT>::ShaderProgramDescStore const &
    MaterialBuilder<IteratorTypeT>::getShaderProgStore (void) const
{
    return _shaderStore;
}

template <class IteratorTypeT>
inline typename MaterialBuilder<IteratorTypeT>::ShaderParamStore &
    MaterialBuilder<IteratorTypeT>::editGlobalParams(void)
{
    return _globalParamStore;
}

template <class IteratorTypeT>
inline typename MaterialBuilder<IteratorTypeT>::ShaderParamStore const &
    MaterialBuilder<IteratorTypeT>::getGlobalParams (void)
{
    return _globalParamStore;
}

/*===========================================================================*/
/* MaterialGrammar<BindBuilderT>                                             */
/*===========================================================================*/

template <class MatBuilderT>
class MaterialGrammar : public bs::grammar<MaterialGrammar<MatBuilderT> >
{
  public:
    typedef MatBuilderT                     MatBuilder;
    
    typedef MaterialGrammar<MatBuilder>     Self;
    typedef bs::grammar    <Self      >     Inherited;

    
    MaterialGrammar(MatBuilder *pBuilder);
    
    template <class ScannerT>
    struct definition
    {
        definition(MaterialGrammar const &self);
        
        bs::rule<ScannerT> const &
        start(void) const;
              
        bs::rule<ScannerT> file;
        bs::rule<ScannerT> identifier;
        bs::rule<ScannerT> name;
        bs::rule<ScannerT> fileName;
        
        bs::rule<ScannerT> materialSpec;
        bs::rule<ScannerT> materialSpecBegin;
        bs::rule<ScannerT> materialSpecEnd;
        bs::rule<ScannerT> materialSpecElement;
        bs::rule<ScannerT> backFaceCullSpec;
        bs::rule<ScannerT> blendFuncSpec;
        bs::rule<ScannerT> textureRef;
        bs::rule<ScannerT> fragmentProgRef;
        bs::rule<ScannerT> vertexProgRef;
        bs::rule<ScannerT> shaderParamSpec;
        bs::rule<ScannerT> shaderParamType;
        bs::rule<ScannerT> shaderParamArray;
        bs::rule<ScannerT> shaderParamName;
        bs::rule<ScannerT> shaderParamValue;
        
        bs::rule<ScannerT> textureSpec;
        bs::rule<ScannerT> textureSpecBegin;
        bs::rule<ScannerT> textureSpecElement;
        bs::rule<ScannerT> textureSpecEnd;
        
        bs::rule<ScannerT> shaderSpec;
        bs::rule<ScannerT> shaderSpecBegin;
        bs::rule<ScannerT> shaderSpecElement;
        bs::rule<ScannerT> shaderSpecEnd;
        
        bs::rule<ScannerT> globalParamSpec;
        bs::rule<ScannerT> globalParamSpecBegin;
        bs::rule<ScannerT> globalParamSpecElement;
        bs::rule<ScannerT> globalParamSpecEnd;
    };
   
  private:
    MatBuilder *_pBuilder;
};

template <class MatBuilderT>
inline
    MaterialGrammar<MatBuilderT>::MaterialGrammar(MatBuilder *pBuilder)
        : _pBuilder(pBuilder)
{
}

template <class MatBuilderT>
template <class ScannerT   >
    MaterialGrammar<MatBuilderT>::definition<ScannerT>::definition(
        MaterialGrammar const &self)
{
    file =
        +(  materialSpec
         |  textureSpec
         |  shaderSpec
         |  globalParamSpec
         )
        ;
        
    identifier =
            (bs::alnum_p | bs::ch_p('_')                )
        >> *(bs::alnum_p | bs::ch_p('_') | bs::ch_p('-'))
        ;
    
    name =
            bs::confix_p(bs::ch_p('\"'),
                         identifier,
                         bs::ch_p('\"') )
        ;
    
    fileName =
            bs::confix_p(bs::ch_p('\"'),
                        +(bs::alnum_p | bs::ch_p('/')  | bs::ch_p('.') | bs::ch_p('_')),
                        bs::ch_p('\"') )
        ;
                            
    materialSpec =
            materialSpecBegin
        >> +materialSpecElement
        >>  materialSpecEnd
        ;
        
    materialSpecBegin = 
            bs::str_p("begin_material")
        >>  name[boost::bind(&MatBuilder::beginMaterial, self._pBuilder, _1, _2)]
        ;
                    
    materialSpecEnd =
            bs::str_p("end_material")[boost::bind(&MatBuilder::endMaterial, self._pBuilder, _1, _2)]
        ;
                
    materialSpecElement =
        (   backFaceCullSpec
        |   blendFuncSpec
        |   textureRef
        |   fragmentProgRef
        |   vertexProgRef
        |   shaderParamSpec
        )
        ;
        
    backFaceCullSpec =
            bs::str_p("cull_face")
        >> (    bs::str_p("none")    
           |    bs::str_p("front")
           |    bs::str_p("back")
           |    bs::str_p("both")
           )[boost::bind(&MatBuilder::setCullFace, self._pBuilder, _1, _2)]
           ;
           
    blendFuncSpec =
            bs::str_p("blend_source")
        >> (    bs::str_p("zero")
           |    bs::str_p("one_minus_src_alpha")
           |    bs::str_p("one")
           |    bs::str_p("src_alpha")
           )[boost::bind(&MatBuilder::setBlendSource, self._pBuilder, _1, _2)]
        >>  bs::str_p("blend_destination")
        >> (    bs::str_p("zero")
           |    bs::str_p("one_minus_src_alpha")
           |    bs::str_p("one")
           |    bs::str_p("src_alpha")
           )[boost::bind(&MatBuilder::setBlendDest, self._pBuilder, _1, _2)]
           ;
        
    textureRef =                        // texture 0 "concrete_wall" "sampler_name"
            bs::str_p("texture")[boost::bind(&MatBuilder::addTexture, self._pBuilder, _1, _2)]
        >>  bs::uint_p[boost::bind(&MatBuilder::setTextureId, self._pBuilder, _1)]
        >>  name[boost::bind(&MatBuilder::setTextureName, self._pBuilder, _1, _2)]
        >>  name[boost::bind(&MatBuilder::setTextureSamplerName, self._pBuilder, _1, _2)]
        >>!(
                bs::uint_p[boost::bind(&MatBuilder::setTextureSizeX, self._pBuilder, _1)]
            >>  bs::uint_p[boost::bind(&MatBuilder::setTextureSizeY, self._pBuilder, _1)]
           )
        ;
        
    fragmentProgRef =                   // fragment_prog "dark_green"
            bs::str_p("fragment_prog")
        >>  name[boost::bind(&MatBuilder::setFPName, self._pBuilder, _1, _2)]
        ;
        
    vertexProgRef =                     // vertex_prog "wave_flag"
            bs::str_p("vertex_prog")
        >>  name[boost::bind(&MatBuilder::setVPName, self._pBuilder, _1, _2)]
        ;
         
    shaderParamSpec =                   // param fp vec3f "light0Pos" "0.0 0.0 0.0"
            bs::str_p("param")[boost::bind(&MatBuilder::addParam, self._pBuilder, _1, _2)]
        >>  shaderParamType
        >> !shaderParamArray
        >>  shaderParamName
        >> !shaderParamArray
        >>  bs::ch_p('=')
        >>  shaderParamValue
        ;
         
    shaderParamType =
        (   bs::str_p("bool")
        |   bs::str_p("int")
        |   bs::str_p("float")
        |   bs::str_p("vec2")
        |   bs::str_p("vec3")
        |   bs::str_p("vec4")
        )[boost::bind(&MatBuilder::setParamType, self._pBuilder, _1, _2)]
        ;
        
    shaderParamArray =
        (   bs::ch_p('[')
        >>  !bs::int_p
        >>  bs::ch_p(']')
        )[boost::bind(&MatBuilder::setParamArray, self._pBuilder, _1, _2)]
        ;
        
    shaderParamName =
            identifier[boost::bind(&MatBuilder::setParamName, self._pBuilder, _1, _2)]
        ;
        
    shaderParamValue =
            bs::confix_p(bs::ch_p('{'),
                         *bs::anychar_p,
                         bs::ch_p('}')
                        )[boost::bind(&MatBuilder::setParamValue, self._pBuilder, _1, _2)]
        ;
        
    textureSpec =
            textureSpecBegin
        >>  textureSpecElement
        >>  textureSpecEnd
        ;
        
    textureSpecBegin = 
            bs::str_p("begin_texture")
        >>  name[boost::bind(&MatBuilder::beginTexture, self._pBuilder, _1, _2)]
        ;
        
    textureSpecElement =
            bs::str_p("file")
        >>  fileName[boost::bind(&MatBuilder::setTextureFile, self._pBuilder, _1, _2)]
        ;
        
    textureSpecEnd =
            bs::str_p("end_texture")[boost::bind(&MatBuilder::endTexture, self._pBuilder, _1, _2)]
        ;
            
    shaderSpec =
            shaderSpecBegin
        >>  shaderSpecElement
        >>  shaderSpecEnd
        ;
        
    shaderSpecBegin =
            bs::str_p("begin_shader")
        >>  name[boost::bind(&MatBuilder::beginShader, self._pBuilder, _1, _2)]
        ;
        
    shaderSpecElement =
            bs::str_p("type")
        >>  (   bs::str_p("vp")
            |   bs::str_p("fp")
            )[boost::bind(&MatBuilder::setShaderType, self._pBuilder, _1, _2)]
        >>  bs::str_p("file")
        >>  fileName[boost::bind(&MatBuilder::setShaderFile, self._pBuilder, _1, _2)]
        ;
        
    shaderSpecEnd =
            bs::str_p("end_shader")[boost::bind(&MatBuilder::endShader, self._pBuilder, _1, _2)]
        ;
        
    globalParamSpec =
            globalParamSpecBegin
        >> +globalParamSpecElement
        >>  globalParamSpecEnd
        ;
        
    globalParamSpecBegin =
            bs::str_p("begin_global_params")[boost::bind(&MatBuilder::beginGlobalParams, self._pBuilder, _1, _2)]
        ;
        
    globalParamSpecElement =                   // param fp vec3f "light0Pos" "0.0 0.0 0.0"
            bs::str_p("param")[boost::bind(&MatBuilder::addParam, self._pBuilder, _1, _2)]
        >>  shaderParamType
        >> !shaderParamArray
        >>  shaderParamName
        >> !shaderParamArray
        >>  bs::ch_p('=')
        >>  shaderParamValue
        ;
    
    globalParamSpecEnd =
            bs::str_p("end_global_params")[boost::bind(&MatBuilder::endGlobalParams, self._pBuilder, _1, _2)]
        ;
    
    BOOST_SPIRIT_DEBUG_NODE(file);
    BOOST_SPIRIT_DEBUG_NODE(identifier);
    BOOST_SPIRIT_DEBUG_NODE(name);
    BOOST_SPIRIT_DEBUG_NODE(fileName);
    
    BOOST_SPIRIT_DEBUG_NODE(materialSpec);
    BOOST_SPIRIT_DEBUG_NODE(materialSpecBegin);
    BOOST_SPIRIT_DEBUG_NODE(materialSpecEnd);
    BOOST_SPIRIT_DEBUG_NODE(materialSpecElement);
    BOOST_SPIRIT_DEBUG_NODE(backFaceCullSpec);
    BOOST_SPIRIT_DEBUG_NODE(blendFuncSpec);
    BOOST_SPIRIT_DEBUG_NODE(textureRef);
    BOOST_SPIRIT_DEBUG_NODE(fragmentProgRef);
    BOOST_SPIRIT_DEBUG_NODE(vertexProgRef);
    BOOST_SPIRIT_DEBUG_NODE(shaderParamSpec);
    BOOST_SPIRIT_DEBUG_NODE(shaderParamType);
    BOOST_SPIRIT_DEBUG_NODE(shaderParamArray);
    BOOST_SPIRIT_DEBUG_NODE(shaderParamName);
    BOOST_SPIRIT_DEBUG_NODE(shaderParamValue);
    
    BOOST_SPIRIT_DEBUG_NODE(textureSpec);
    BOOST_SPIRIT_DEBUG_NODE(textureSpecBegin);
    BOOST_SPIRIT_DEBUG_NODE(textureSpecElement);
    BOOST_SPIRIT_DEBUG_NODE(textureSpecEnd);
    
    BOOST_SPIRIT_DEBUG_NODE(shaderSpec);
    BOOST_SPIRIT_DEBUG_NODE(shaderSpecBegin);
    BOOST_SPIRIT_DEBUG_NODE(shaderSpecElement);
    BOOST_SPIRIT_DEBUG_NODE(shaderSpecEnd);
    
    BOOST_SPIRIT_DEBUG_NODE(globalParamSpec);
    BOOST_SPIRIT_DEBUG_NODE(globalParamSpecBegin);
    BOOST_SPIRIT_DEBUG_NODE(globalParamSpecElement);
    BOOST_SPIRIT_DEBUG_NODE(globalParamSpecEnd);
};

template <class MatBuilderT>
template <class ScannerT   >
inline bs::rule<ScannerT> const &
    MaterialGrammar<MatBuilderT>::definition<ScannerT>::start(void) const
{
    return file;
}

// limit debugging to this translation unit
#ifdef BOOST_SPIRIT_DEBUG
#undef BOOST_SPIRIT_DEBUG
#endif

#endif // _MATERIALPARSER_H_
