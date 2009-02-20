
#ifndef _EXTRUSIONPARSER_H_
#define _EXTRUSIONPARSER_H_

// boost spirit includes

// @note: Lets not define this as at this point its not printing any useful data. 
//#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/bind.hpp>

// OpenSG includes
#include <OpenSG/OSGVector.h>

// std library includes
#include <string>
#include <vector>

namespace bs = boost::spirit;

/*===========================================================================*/
/* ExtrusionBuilder<IteratorTypeT>                                           */
/*===========================================================================*/

template <class IteratorTypeT>
class ExtrusionBuilder
{
  public:
    typedef IteratorTypeT                           IteratorType;
    typedef ExtrusionBuilder<IteratorType>          Self;
      
    typedef std::vector<ExtrusionDesc>              ExtrusionStore;
    typedef typename ExtrusionStore::iterator       ExtrusionStoreIt;
    typedef typename ExtrusionStore::const_iterator ExtrusionStoreConstIt;
    
    explicit ExtrusionBuilder(void);
    
    void addExtrusion(IteratorType begin,     IteratorType end    );
    void setName     (IteratorType nameBegin, IteratorType nameEnd);
    
    void addXSCP(IteratorType begin, IteratorType end  );
    void setXSCP(unsigned int index, float        value);
    void addXSSP(float        value                    );
    
    void addSpineCurve(IteratorType begin,     IteratorType end    );
    void addSpineCP   (IteratorType beginName, IteratorType endName);
    void addSpineSP   (float        value                          );
    
    void setUp(unsigned int index, float value);
  
    
    ExtrusionStore _extStore;
};


template <class IteratorTypeT>
inline
    ExtrusionBuilder<IteratorTypeT>::ExtrusionBuilder(void)
{
}

template <class IteratorTypeT>
inline void
    ExtrusionBuilder<IteratorTypeT>::addExtrusion(
        IteratorType begin, IteratorType end)
{
  _extStore.push_back(ExtrusionDesc());
}

template <class IteratorTypeT>
inline void
    ExtrusionBuilder<IteratorTypeT>::setName(
        IteratorType nameBegin, IteratorType nameEnd)
{
    std::string extName(nameBegin, nameEnd);

    _extStore.back()._name = extName.substr(1, extName.length() - 2);
    
    //std::cout << "setName " << extName << std::endl;
}

template <class IteratorTypeT>
inline void
    ExtrusionBuilder<IteratorTypeT>::addXSCP(
        IteratorType begin, IteratorType end)
{
    //std::cout << "addXSCP" << std::endl;

    _extStore.back()._crossSectionCP.push_back(OSG::Pnt2f());
}

template <class IteratorTypeT>
inline void
    ExtrusionBuilder<IteratorTypeT>::setXSCP(unsigned int index, float value)
{
    //std::cout << "setXSCP [" << index << "] [" << value << "]" << std::endl;

    _extStore.back()._crossSectionCP.back()[index] = value;
}

template <class IteratorTypeT>
inline void
    ExtrusionBuilder<IteratorTypeT>::addXSSP(float value)
{
    //std::cout << "addXSSP [" << value << "]" << std::endl;

    _extStore.back()._crossSectionSamples.push_back(value);
}

template <class IteratorTypeT>
inline void
    ExtrusionBuilder<IteratorTypeT>::addSpineCurve(
        IteratorType begin, IteratorType end)
{
    //std::cout << "addSpineCurve" << std::endl;

    _extStore.back()._spineCurveLengths.push_back(0);
}

template <class IteratorTypeT>
inline void
    ExtrusionBuilder<IteratorTypeT>::addSpineCP(
        IteratorType beginName, IteratorType endName)
{
    std::string cpName(beginName, endName);

    _extStore.back()._spineCurveLengths.back() += 1;
    _extStore.back()._spineCPNames.push_back(cpName.substr(1, cpName.length() - 2));
    
    //std::cout << "addSpineCP [" << cpName << "]" << std::endl;
}

template <class IteratorTypeT>
inline void
    ExtrusionBuilder<IteratorTypeT>::addSpineSP(float value)
{
    //std::cout << "addSpineSP [" << value << "]" << std::endl;

    _extStore.back()._spineSamples.push_back(value);
}

template <class IteratorTypeT>
inline void
    ExtrusionBuilder<IteratorTypeT>::setUp(unsigned int index, float value)
{
    //std::cout << "setUp [" << index << "] [" << value << "]" << std::endl;

    _extStore.back()._upVector[index] = value;
}

/*===========================================================================*/
/* ExtrusionGrammar<ExtBuilderT>                                             */
/*===========================================================================*/

template <class ExtBuilderT>
class ExtrusionGrammar : public bs::grammar<ExtrusionGrammar<ExtBuilderT> >
{
  public:
    typedef ExtBuilderT                     ExtBuilder;
    
    typedef ExtrusionGrammar<ExtBuilderT>   Self;
    typedef bs::grammar     <Self      >    Inherited;

    
    ExtrusionGrammar(ExtBuilder *pBuilder);
    
    template <class ScannerT>
    struct definition
    {
        definition(ExtrusionGrammar const &self);
        
        bs::rule<ScannerT> const &
        start(void) const;
        
        bs::rule<ScannerT> file;
        bs::rule<ScannerT> identifier;
        bs::rule<ScannerT> name;
        bs::rule<ScannerT> extRecord;
        bs::rule<ScannerT> crossSectionRecord;
        bs::rule<ScannerT> crossSectionCP;
        bs::rule<ScannerT> crossSectionSP;
        bs::rule<ScannerT> spineRecord;
        bs::rule<ScannerT> spineCurveRecord;
        bs::rule<ScannerT> spineCP;
        bs::rule<ScannerT> spineSP;
        bs::rule<ScannerT> upVectorRecord;
    };
    
  private:
    ExtBuilder *_pBuilder;
};

template <class ExtBuilderT>
inline
    ExtrusionGrammar<ExtBuilderT>::ExtrusionGrammar(ExtBuilder *pBuilder)
    
    : _pBuilder(pBuilder)
{
    // nothing to do
}

template <class ExtBuilderT>
template <class ScannerT   >
inline
    ExtrusionGrammar<ExtBuilderT>::definition<ScannerT>::definition(
        ExtrusionGrammar const &self)
{
    file =
           +extRecord
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
        
    extRecord =
            bs::str_p("begin_extrusion")[boost::bind(&ExtBuilder::addExtrusion, self._pBuilder, _1, _2)]
        >>  name[boost::bind(&ExtBuilder::setName, self._pBuilder, _1, _2)]
        >>  crossSectionRecord
        >>  spineRecord
        >>  upVectorRecord
        >>  bs::str_p("end_extrusion")
        ;
        
    crossSectionRecord =
            bs::str_p("begin_cross_section")
        >> +crossSectionCP
        >> +crossSectionSP
        >>  bs::str_p("end_cross_section")
        ;
        
    crossSectionCP =
            bs::str_p("control_point")[boost::bind(&ExtBuilder::addXSCP, self._pBuilder, _1, _2)]
        >>  bs::real_p[boost::bind(&ExtBuilder::setXSCP, self._pBuilder, 0, _1)]
        >>  bs::real_p[boost::bind(&ExtBuilder::setXSCP, self._pBuilder, 1, _1)]
        ;
        
    crossSectionSP =
            bs::str_p("sample_point")
        >>  bs::real_p[boost::bind(&ExtBuilder::addXSSP, self._pBuilder, _1)]
        ;
    
    spineRecord =
            bs::str_p("begin_spine")
        >>  spineCurveRecord
        >>  bs::str_p("end_spine")
        ;

    spineCurveRecord =
            bs::str_p("begin_curve")[boost::bind(&ExtBuilder::addSpineCurve, self._pBuilder, _1, _2)]
        >> +spineCP
        >> +spineSP
        >>  bs::str_p("end_curve")
        ;
        
    spineCP =
            bs::str_p("control_point")
        >>  name[boost::bind(&ExtBuilder::addSpineCP, self._pBuilder, _1, _2)]
        ;
        
    spineSP =
            bs::str_p("sample_point")
        >>  bs::real_p[boost::bind(&ExtBuilder::addSpineSP, self._pBuilder, _1)]
        ;
        
    upVectorRecord =
            bs::str_p("up_vector")
        >>  bs::real_p[boost::bind(&ExtBuilder::setUp, self._pBuilder, 0, _1)]
        >>  bs::real_p[boost::bind(&ExtBuilder::setUp, self._pBuilder, 1, _1)]
        >>  bs::real_p[boost::bind(&ExtBuilder::setUp, self._pBuilder, 2, _1)]
        ;
        
    BOOST_SPIRIT_DEBUG_NODE(file);
    BOOST_SPIRIT_DEBUG_NODE(identifier);
    BOOST_SPIRIT_DEBUG_NODE(name);
    BOOST_SPIRIT_DEBUG_NODE(extRecord);
    BOOST_SPIRIT_DEBUG_NODE(crossSectionRecord);
    BOOST_SPIRIT_DEBUG_NODE(crossSectionCP);
    BOOST_SPIRIT_DEBUG_NODE(crossSectionSP);
    BOOST_SPIRIT_DEBUG_NODE(spineRecord);
    BOOST_SPIRIT_DEBUG_NODE(spineCurveRecord);
    BOOST_SPIRIT_DEBUG_NODE(spineCP);
    BOOST_SPIRIT_DEBUG_NODE(spineSP);
    BOOST_SPIRIT_DEBUG_NODE(upVectorRecord);
}

template <class ExtBuilderT>
template <class ScannerT   >
inline bs::rule<ScannerT> const &
    ExtrusionGrammar<ExtBuilderT>::definition<ScannerT>::start(void) const
{
    std::cout << "ExtrusionGrammar: " << std::endl;
    return file;
}

// limit debugging to this translation unit
#ifdef BOOST_SPIRIT_DEBUG
#undef BOOST_SPIRIT_DEBUG
#endif

#endif // _EXTRUSIONPARSER_H_
