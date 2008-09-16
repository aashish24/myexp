
#ifndef _ANIMATIONPARSER_H_
#define _ANIMATIONPARSER_H_

#include <Descriptors.h>

// boost includes
// #define BOOST_SPIRIT_DEBUG
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/bind.hpp>

// debug includes
#include <iostream>

namespace bs = boost::spirit;

template <class IteratorTypeT>
class AnimationBuilder
{
  public:
    typedef IteratorTypeT                   IteratorType;
    typedef AnimationBuilder<IteratorType>  Self;
        
    
    typedef std::vector<KeyframeAnimationDesc>      AnimationStore;
    typedef typename AnimationStore::iterator       AnimationStoreIt;
    typedef typename AnimationStore::const_iterator AnimationStoreConstIt;
    typedef KeyframeAnimationDesc::Keyframe         Keyframe;
    typedef KeyframeAnimationDesc::TrackTypeE       TrackTypeE;
    
    explicit AnimationBuilder(void);
    
    
    void beginAnim       (IteratorTypeT nameBegin,
                          IteratorTypeT nameEnd   );
    void addKeyframeTime (unsigned int  index,
                          float         time);
    void addKeyframeValue(unsigned int  index,
                          float         time      );
    void pushKeyframe    (TrackTypeE    track,
                          IteratorTypeT begin,
                          IteratorTypeT end       );
    
    void endAnim         (IteratorTypeT begin,
                          IteratorTypeT end       );
  
                          
    AnimationStore const &getAnimStore (void) const;
    AnimationStore       &editAnimStore(void);
  private:
    AnimationStore _animStore;
    Keyframe       _currKeyframe;
};

template <class IteratorTypeT>
inline
    AnimationBuilder<IteratorTypeT>::AnimationBuilder(void)
    
    : _animStore   (),
      _currKeyframe()
{
    // nothing to do
}

template <class IteratorTypeT>
inline void
    AnimationBuilder<IteratorTypeT>::beginAnim(
        IteratorTypeT nameBegin, IteratorTypeT nameEnd)
{
    std::string objName(nameBegin, nameEnd);

    _animStore.push_back(KeyframeAnimationDesc());
    _animStore.back()._name = objName.substr(1, objName.length() - 2);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cout << "beginAnim " << objName << "\n";
#endif
}

template <class IteratorTypeT>
inline void
    AnimationBuilder<IteratorTypeT>::addKeyframeTime(
        unsigned int index, float time)
{
    _currKeyframe._cp[index][0] = time;
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cout << "addKeyframeTime " << time << "\n";
#endif
}

template <class IteratorTypeT>
inline void
    AnimationBuilder<IteratorTypeT>::addKeyframeValue(
        unsigned int index, float value)
{
    _currKeyframe._cp[index][1] = value;
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cout << "addKeyframeValue " << value << "\n";
#endif
}

template <class IteratorTypeT>
inline void
    AnimationBuilder<IteratorTypeT>::pushKeyframe(
        TrackTypeE track, IteratorTypeT begin, IteratorTypeT end)
{
    _animStore.back()._animTracks[track].push_back(_currKeyframe);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cout << "pushKeyframe ";
    _currKeyframe.dump(std::cout);
    std::cout << "\n";
#endif
}

template <class IteratorTypeT>
inline void
    AnimationBuilder<IteratorTypeT>::endAnim(
        IteratorTypeT begin, IteratorTypeT end)
{
    for(unsigned int i = 0; i < KeyframeAnimationDesc::numTracksDesc; ++i)
    {
        if(_animStore.back()._animTracks[i].size() > 0)
            return;
    }
    
    // if all tracks are empty, remove the (empty) animation
    _animStore.pop_back();
}

template <class IteratorTypeT>
inline typename AnimationBuilder<IteratorTypeT>::AnimationStore const &
    AnimationBuilder<IteratorTypeT>::getAnimStore(void) const
{
    return _animStore;
}

template <class IteratorTypeT>
inline typename AnimationBuilder<IteratorTypeT>::AnimationStore &
    AnimationBuilder<IteratorTypeT>::editAnimStore(void)
{
    return _animStore;
}

/*===========================================================================*/
/* AnimationGrammar<AnimBuilderT>                                            */
/*===========================================================================*/

template <class AnimBuilderT>
class AnimationGrammar : public bs::grammar<AnimationGrammar<AnimBuilderT> >
{
  public:
    typedef AnimBuilderT                   AnimBuilder;
    
    typedef AnimationGrammar<AnimBuilder>  Self;
    typedef bs::grammar     <Self      >   Inherited;

    
    AnimationGrammar(AnimBuilder *pBuilder);
    
    template <class ScannerT>
    struct definition
    {
        definition(AnimationGrammar const &self);
        
        bs::rule<ScannerT> const &
        start(void) const;
        
        bs::rule<ScannerT> file;
        bs::rule<ScannerT> identifier;
        bs::rule<ScannerT> name;
        
        bs::rule<ScannerT> animRecord;
        bs::rule<ScannerT> animTracks;
        bs::rule<ScannerT> animTrackPosX;
        bs::rule<ScannerT> animTrackPosY;
        bs::rule<ScannerT> animTrackPosZ;
        bs::rule<ScannerT> animTrackRotX;
        bs::rule<ScannerT> animTrackRotY;
        bs::rule<ScannerT> animTrackRotZ;
        bs::rule<ScannerT> animTrackScaleX;
        bs::rule<ScannerT> animTrackScaleY;
        bs::rule<ScannerT> animTrackScaleZ;
        bs::rule<ScannerT> animInitialKeyframe;
        bs::rule<ScannerT> animCentralKeyframe;
        bs::rule<ScannerT> animFinalKeyframe;
        
    };
    
  private:
    AnimBuilder *_pBuilder;
};

template <class AnimBuilderT>
inline
    AnimationGrammar<AnimBuilderT>::AnimationGrammar(AnimBuilder *pBuilder)
    
    : _pBuilder(pBuilder)
{
}

template <class AnimBuilderT>
template <class ScannerT    >
inline
    AnimationGrammar<AnimBuilderT>::definition<ScannerT>::definition(
        AnimationGrammar const &self)
{
    file =
           +animRecord
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
            
    animRecord =
            bs::str_p("begin_animation")
        >>  bs::str_p("object")
        >>  name[boost::bind(&AnimBuilder::beginAnim, self._pBuilder, _1, _2)]
        >>  animTracks
        >>  bs::str_p("end_animation")[boost::bind(&AnimBuilder::endAnim, self._pBuilder, _1, _2)]
        ;
        
    animTracks =
           !animTrackPosX
        >> !animTrackPosY
        >> !animTrackPosZ
        >> !animTrackRotX
        >> !animTrackRotY
        >> !animTrackRotZ
        >> !animTrackScaleX
        >> !animTrackScaleY
        >> !animTrackScaleZ
        ;
    
    animTrackPosX =
            bs::str_p("begin_x_position")
        >> !(       animInitialKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_X, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_X, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_X, _1, _2)]
            )
        >>  bs::str_p("end_x_position")
        ;
        
    animTrackPosY =
            bs::str_p("begin_y_position")
        >> !(       animInitialKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Y, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Y, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Y, _1, _2)]
            )
        >>  bs::str_p("end_y_position")
        ;
        
    animTrackPosZ =
            bs::str_p("begin_z_position")
        >> !(       animInitialKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Z, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Z, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Z, _1, _2)]
            )
        >>  bs::str_p("end_z_position")
        ;
        
    animTrackRotX =
            bs::str_p("begin_x_rotation")
        >> !(       animInitialKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_X, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_X, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_X, _1, _2)]
            )
        >>  bs::str_p("end_x_rotation")
        ;
        
    animTrackRotY =
            bs::str_p("begin_y_rotation")
        >> !(       animInitialKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Y, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Y, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Y, _1, _2)]
            )
        >>  bs::str_p("end_y_rotation")
        ;
        
    animTrackRotZ =
            bs::str_p("begin_z_rotation")
        >> !(       animInitialKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Z, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Z, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Z, _1, _2)]
            )
        >>  bs::str_p("end_z_rotation")
        ;
        
    animTrackScaleX =
            bs::str_p("begin_x_scale")
        >> !(       animInitialKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_X, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_X, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_X, _1, _2)]
            )
        >>  bs::str_p("end_x_scale")
        ;
        
    animTrackScaleY =
            bs::str_p("begin_y_scale")
        >> !(       animInitialKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_Y, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_Y, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_Y, _1, _2)]
            )
        >>  bs::str_p("end_y_scale")
        ;
        
    animTrackScaleZ =
            bs::str_p("begin_z_scale")
        >> !(       animInitialKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_Z, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_Z, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&AnimBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_Z, _1, _2)]
            )
        >>  bs::str_p("end_z_scale")
        ;
               
    animInitialKeyframe =
            bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_OUT, _1)]
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_OUT, _1)]
        ;
        
    animCentralKeyframe =
            bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_IN, _1)]
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_IN, _1)]
        >>  bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_OUT, _1)]
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_OUT, _1)]
        ;
        
    animFinalKeyframe =
            bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_IN, _1)]
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_IN, _1)]
        >>  bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::real_p[boost::bind(&AnimBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        ;
        
    BOOST_SPIRIT_DEBUG_NODE(file);
    BOOST_SPIRIT_DEBUG_NODE(identifier);
    BOOST_SPIRIT_DEBUG_NODE(name);
    BOOST_SPIRIT_DEBUG_NODE(animRecord);
    BOOST_SPIRIT_DEBUG_NODE(animTracks);
    BOOST_SPIRIT_DEBUG_NODE(animTrackPosX);
    BOOST_SPIRIT_DEBUG_NODE(animTrackPosY);
    BOOST_SPIRIT_DEBUG_NODE(animTrackPosZ);
    BOOST_SPIRIT_DEBUG_NODE(animTrackRotX);
    BOOST_SPIRIT_DEBUG_NODE(animTrackRotY);
    BOOST_SPIRIT_DEBUG_NODE(animTrackRotZ);
    BOOST_SPIRIT_DEBUG_NODE(animTrackScaleX);
    BOOST_SPIRIT_DEBUG_NODE(animTrackScaleY);
    BOOST_SPIRIT_DEBUG_NODE(animTrackScaleZ);
    BOOST_SPIRIT_DEBUG_NODE(animInitialKeyframe);
    BOOST_SPIRIT_DEBUG_NODE(animCentralKeyframe);
    BOOST_SPIRIT_DEBUG_NODE(animFinalKeyframe);
    
}

template <class AnimBuilderT>
template <class ScannerT    >
inline bs::rule<ScannerT> const &
    AnimationGrammar<AnimBuilderT>::definition<ScannerT>::start(void) const
{
    return file;
}

// limit debugging to this translation unit
#ifdef BOOST_SPIRIT_DEBUG
#undef BOOST_SPIRIT_DEBUG
#endif

#endif // _ANIMATIONPARSER_H_

