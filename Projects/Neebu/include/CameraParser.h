
#ifndef _CAMERAPARSER_H_
#define _CAMERAPARSER_H_

#include <Descriptors.h>

// boost includes
// #define BOOST_SPIRIT_DEBUG
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/bind.hpp>

// debug includes
#include <iostream>

namespace bs = boost::spirit;

// #define BOOST_SPIRIT_DEBUG

template <class IteratorTypeT>
class CameraBuilder
{
  public:
    typedef IteratorTypeT                IteratorType;
    typedef CameraBuilder<IteratorType>  Self;
    
    
    
    typedef std::vector<KeyframeAnimationDesc>   CameraStore;
    typedef typename CameraStore::iterator       CameraStoreIt;
    typedef typename CameraStore::const_iterator CameraStoreConstIt;
    typedef KeyframeAnimationDesc::Keyframe      Keyframe;
    typedef KeyframeAnimationDesc::TrackTypeE    TrackTypeE;
    
    explicit CameraBuilder(void);
    
    
    void beginAnim       (IteratorTypeT nameBegin,
                          IteratorTypeT nameEnd   );
    void addKeyframeTime (unsigned int  index,
                          double         time);
    void addKeyframeValue(unsigned int  index,
                          double         time      );
    void pushKeyframe    (TrackTypeE    track,
                          IteratorTypeT begin,
                          IteratorTypeT end       );
    
    void endAnim         (IteratorTypeT begin,
                          IteratorTypeT end       );
  
                          
    CameraStore const &getCamStore (void) const;
    CameraStore       &editCamStore(void);
  private:
    CameraStore    _camStore;
    Keyframe       _currKeyframe;
};

template <class IteratorTypeT>
inline
    CameraBuilder<IteratorTypeT>::CameraBuilder(void)
    
    : _camStore   (),
      _currKeyframe()
{
    // nothing to do
}

template <class IteratorTypeT>
inline void
    CameraBuilder<IteratorTypeT>::beginAnim(
        IteratorTypeT nameBegin, IteratorTypeT nameEnd)
{
    std::string objName(nameBegin, nameEnd);

    _camStore.push_back(KeyframeAnimationDesc());
    _camStore.back()._name = objName.substr(1, objName.length() - 2);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cout << "beginCam " << objName << "\n";
#endif
}

template <class IteratorTypeT>
inline void
    CameraBuilder<IteratorTypeT>::addKeyframeTime(
        unsigned int index, double time)
{
    _currKeyframe._cp[index][0] = time;
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cout << "addKeyframeTime " << time << "\n";
#endif
}

template <class IteratorTypeT>
inline void
    CameraBuilder<IteratorTypeT>::addKeyframeValue(
        unsigned int index, double value)
{
    _currKeyframe._cp[index][1] = value;
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cout << "addKeyframeValue " << value << "\n";
#endif
}

template <class IteratorTypeT>
inline void
    CameraBuilder<IteratorTypeT>::pushKeyframe(
        TrackTypeE track, IteratorTypeT begin, IteratorTypeT end)
{
    _camStore.back()._animTracks[track]._keyFrames.push_back(_currKeyframe);
    
#ifdef BOOST_SPIRIT_DEBUG
    std::cout << "pushKeyframe ";
    _currKeyframe.dump(std::cout);
    std::cout << "\n";
#endif
}

template <class IteratorTypeT>
inline void
    CameraBuilder<IteratorTypeT>::endAnim(
        IteratorTypeT begin, IteratorTypeT end)
{
    for(unsigned int i = 0; i < KeyframeAnimationDesc::numTracks; ++i)
    {
        if(_camStore.back()._animTracks[i]._keyFrames.size() > 0)
            return;
    }
    
    // if all tracks are empty, remove the (empty) animation
    _camStore.pop_back();
}

template <class IteratorTypeT>
inline typename CameraBuilder<IteratorTypeT>::CameraStore const &
    CameraBuilder<IteratorTypeT>::getCamStore(void) const
{
    return _camStore;
}

template <class IteratorTypeT>
inline typename CameraBuilder<IteratorTypeT>::CameraStore &
    CameraBuilder<IteratorTypeT>::editCamStore(void)
{
    return _camStore;
}

/*===========================================================================*/
/* CameraGrammar<AnimBuilderT>                                               */
/*===========================================================================*/

template <class CamBuilderT>
class CameraGrammar : public bs::grammar<CameraGrammar<CamBuilderT> >
{
  public:
    typedef CamBuilderT                   CamBuilder;
    
    typedef CameraGrammar<CamBuilder>  Self;
    typedef bs::grammar  <Self      >  Inherited;

    
    CameraGrammar(CamBuilder *pBuilder);
    
    template <class ScannerT>
    struct definition
    {
        definition(CameraGrammar const &self);
        
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
/*      bs::rule<ScannerT> animTrackScaleX;
        bs::rule<ScannerT> animTrackScaleY;
        bs::rule<ScannerT> animTrackScaleZ;
*/      bs::rule<ScannerT> animInitialKeyframe;
        bs::rule<ScannerT> animCentralKeyframe;
        bs::rule<ScannerT> animFinalKeyframe;
        
    };
    
  private:
    CamBuilder *_pBuilder;
};

template <class AnimBuilderT>
inline
    CameraGrammar<AnimBuilderT>::CameraGrammar(CamBuilder *pBuilder)
    
    : _pBuilder(pBuilder)
{
}

template <class CamBuilderT>
template <class ScannerT   >
inline
    CameraGrammar<CamBuilderT>::definition<ScannerT>::definition(
        CameraGrammar const &self)
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
        >>  name[boost::bind(&CamBuilder::beginAnim, self._pBuilder, _1, _2)]
        >>  animTracks
        >>  bs::str_p("end_animation")[boost::bind(&CamBuilder::endAnim, self._pBuilder, _1, _2)]
        ;
        
    animTracks =
           !animTrackPosX
        >> !animTrackPosY
        >> !animTrackPosZ
        >> !animTrackRotX
        >> !animTrackRotY
        >> !animTrackRotZ
/*      >> !animTrackScaleX
        >> !animTrackScaleY
        >> !animTrackScaleZ
*/        
        ;
    
    animTrackPosX =
            bs::str_p("begin_x_position")
        >> !(       animInitialKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_X, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_X, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_X, _1, _2)]
            )
        >>  bs::str_p("end_x_position")
        ;
        
    animTrackPosY =
            bs::str_p("begin_y_position")
        >> !(       animInitialKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Y, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Y, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Y, _1, _2)]
            )
        >>  bs::str_p("end_y_position")
        ;
        
    animTrackPosZ =
            bs::str_p("begin_z_position")
        >> !(       animInitialKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Z, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Z, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_POS_Z, _1, _2)]
            )
        >>  bs::str_p("end_z_position")
        ;
        
    animTrackRotX =
            bs::str_p("begin_x_rotation")
        >> !(       animInitialKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_X, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_X, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_X, _1, _2)]
            )
        >>  bs::str_p("end_x_rotation")
        ;
        
    animTrackRotY =
            bs::str_p("begin_y_rotation")
        >> !(       animInitialKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Y, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Y, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Y, _1, _2)]
            )
        >>  bs::str_p("end_y_rotation")
        ;
        
    animTrackRotZ =
            bs::str_p("begin_z_rotation")
        >> !(       animInitialKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Z, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Z, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_ROT_Z, _1, _2)]
            )
        >>  bs::str_p("end_z_rotation")
        ;

/*    
    animTrackScaleX =
            bs::str_p("begin_x_scale")
        >> !(       animInitialKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_X, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_X, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_X, _1, _2)]
            )
        >>  bs::str_p("end_x_scale")
        ;
        
    animTrackScaleY =
            bs::str_p("begin_y_scale")
        >> !(       animInitialKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_Y, _1, _2)]
                >> *animCentralKeyframe[boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_Y, _1, _2)]
                >>  animFinalKeyframe  [boost::bind(&CamBuilder::pushKeyframe, self._pBuilder, KeyframeAnimationDesc::TRACK_SCALE_Y, _1, _2)]
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
*/               
    animInitialKeyframe =
            bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_OUT, _1)]
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_OUT, _1)]
        ;
        
    animCentralKeyframe =
            bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_IN, _1)]
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_IN, _1)]
        >>  bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_OUT, _1)]
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_OUT, _1)]
        ;
        
    animFinalKeyframe =
            bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_IN, _1)]
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_IN, _1)]
        >>  bs::str_p("control_point")
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeTime,  self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
        >>  bs::real_p[boost::bind(&CamBuilder::addKeyframeValue, self._pBuilder, KeyframeAnimationDesc::CP_AT, _1)]
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
/*  BOOST_SPIRIT_DEBUG_NODE(animTrackScaleX);
    BOOST_SPIRIT_DEBUG_NODE(animTrackScaleY);
    BOOST_SPIRIT_DEBUG_NODE(animTrackScaleZ);
*/    
    BOOST_SPIRIT_DEBUG_NODE(animInitialKeyframe);
    BOOST_SPIRIT_DEBUG_NODE(animCentralKeyframe);
    BOOST_SPIRIT_DEBUG_NODE(animFinalKeyframe);
    
}

template <class CamBuilderT>
template <class ScannerT    >
inline bs::rule<ScannerT> const &
    CameraGrammar<CamBuilderT>::definition<ScannerT>::start(void) const
{
    return file;
}

// limit debugging to this translation unit
#ifdef BOOST_SPIRIT_DEBUG
#undef BOOST_SPIRIT_DEBUG
#endif

#endif // _CAMERAPARSER_H_

