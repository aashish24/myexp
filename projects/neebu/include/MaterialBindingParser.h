
#ifndef _MATERIALBINDINGPARSER_H_
#define _MATERIALBINDINGPARSER_H_

#include <MaterialBinder.h>

// boost spirit includes
// #define BOOST_SPIRIT_DEBUG
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/bind.hpp>

// std library includes
#include <string>
#include <vector>

namespace bs = boost::spirit;

/*===========================================================================*/
/* BindingBuilder<IteratorTypeT>                                             */
/*===========================================================================*/

template <class IteratorTypeT>
class BindingBuilder
{
  public:
    typedef IteratorTypeT                      IteratorType;
    typedef BindingBuilder<IteratorType>       Self;
  
    typedef std::pair  <std::string, std::string> BindStringMapEntry;
    typedef std::vector<BindStringMapEntry      > BindStringMap;
    
    explicit BindingBuilder(void);
    
    void beginBinding   (IteratorType begin,     IteratorType end    );
    void setObjectName  (IteratorType nameBegin, IteratorType nameEnd);
    void setMaterialName(IteratorType nameBegin, IteratorType nameEnd);
    void endBinding     (IteratorType begin,     IteratorType end    );
    
    BindStringMap const &getBindMap (void) const;
    BindStringMap       &editBindMap(void);
    
  private:
    BindStringMap _bindMap;
    std::string   _objName;
    std::string   _matName;
};

template <class IteratorTypeT>
inline
    BindingBuilder<IteratorTypeT>::BindingBuilder(void)
    
    : _bindMap(),
      _objName(),
      _matName()
{
}

template <class IteratorTypeT>
inline void 
    BindingBuilder<IteratorTypeT>::beginBinding(
        IteratorType begin, IteratorType end)
{
}

template <class IteratorTypeT>
inline void
    BindingBuilder<IteratorTypeT>::setObjectName(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string objName(nameBegin, nameEnd);
    objName = objName.substr(1, objName.length() - 2);

    _objName = objName;
    
    // std::cerr << "setObjectName: " << _objName << "\n";
}

template <class IteratorTypeT>
inline void
    BindingBuilder<IteratorTypeT>::setMaterialName(
        IteratorType nameBegin, IteratorType nameEnd)
{
    _matName.assign(nameBegin, nameEnd);
    
    // std::cerr << "setMaterialName: " << _matName << "\n";
}

template <class IteratorTypeT>
inline void
    BindingBuilder<IteratorTypeT>::endBinding(
        IteratorType begin, IteratorType end)
{
    // std::cerr << "endBinding: " << _objName << " -> " << _matName << "\n";

    _bindMap.push_back(BindStringMapEntry(_objName, _matName));
}

template <class IteratorTypeT>
inline typename BindingBuilder<IteratorTypeT>::BindStringMap const &
    BindingBuilder<IteratorTypeT>::getBindMap (void) const
{
    return _bindMap;
}

template <class IteratorTypeT>
inline typename BindingBuilder<IteratorTypeT>::BindStringMap &
    BindingBuilder<IteratorTypeT>::editBindMap(void)
{
    return _bindMap;
}

/*===========================================================================*/
/* BindingGrammar<BindBuilderT>                                              */
/*===========================================================================*/

template <class BindBuilderT>
class BindingGrammar : public bs::grammar<BindingGrammar<BindBuilderT> >
{
  public:
    typedef BindBuilderT                   BindBuilder;
    
    typedef BindingGrammar<BindBuilder>    Self;
    typedef bs::grammar   <Self      >     Inherited;

    
    BindingGrammar(BindBuilder *pBuilder);
    
    template <class ScannerT>
    struct definition
    {
        definition(BindingGrammar const &self);
        
        bs::rule<ScannerT> const &
        start(void) const;
        
        bs::rule<ScannerT> file;
        bs::rule<ScannerT> identifier;
        bs::rule<ScannerT> matBindingSpec;
        bs::rule<ScannerT> objectNameRegEx;
        bs::rule<ScannerT> materialName;
    };
    
  private:
    BindBuilder *_pBuilder;
};

template <class BindBuilderT>
inline
    BindingGrammar<BindBuilderT>::BindingGrammar(BindBuilder *pBuilder)
    
    : _pBuilder(pBuilder)
{
}

template <class BindBuilderT>
template <class ScannerT    >
inline
    BindingGrammar<BindBuilderT>::definition<ScannerT>::definition(
        BindingGrammar const &self)
{
    file =
            +matBindingSpec[boost::bind(&BindBuilder::endBinding, self._pBuilder, _1, _2)];
        
    identifier =
            (bs::alnum_p | bs::ch_p('_')                )
        >> *(bs::alnum_p | bs::ch_p('_') | bs::ch_p('-'));
            
    matBindingSpec =
            objectNameRegEx
        >>  materialName;
        
    objectNameRegEx =
            bs::confix_p(bs::ch_p('\"'),
                         +bs::anychar_p,
                         bs::ch_p('\"') )[boost::bind(&BindBuilder::setObjectName, self._pBuilder, _1, _2)];
        
    materialName =
            identifier[boost::bind(&BindBuilder::setMaterialName, self._pBuilder, _1, _2)];
            
            
    BOOST_SPIRIT_DEBUG_NODE(file);
    BOOST_SPIRIT_DEBUG_NODE(identifier);
    
    BOOST_SPIRIT_DEBUG_NODE(matBindingSpec);
    
    BOOST_SPIRIT_DEBUG_NODE(objectNameRegEx);
    BOOST_SPIRIT_DEBUG_NODE(materialName);
}

template <class BindBuilderT>
template <class ScannerT    >
inline bs::rule<ScannerT> const &
    BindingGrammar<BindBuilderT>::definition<ScannerT>::start(void) const
{
    return file;
}

// limit debugging to this translation unit
#ifdef BOOST_SPIRIT_DEBUG
#undef BOOST_SPIRIT_DEBUG
#endif

#endif // _MATERIALBINDINGPARSER_H_
