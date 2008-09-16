
#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

// OpenSG include
#include <OpenSG/OSGShaderParameter.h>

// gmtl includes
#include <gmtl/Vec.h>

// std library includes
#include <iosfwd>
#include <string>
#include <vector>
#include <functional>

/*===========================================================================*/
/* DescBase                                                                  */

struct DescBase
{
    virtual ~DescBase(void);

    virtual void dump(std::ostream &os) const;

    std::string _name;
};

// function to compare exact name
// used when (re-)loading materials
class hasThisName: public std::unary_function<DescBase&,bool>{
public:
	hasThisName(const std::string &s) {_s = s;}
	~hasThisName(){;}
	result_type operator()(const argument_type param) const {
		return (param._name.compare(_s) == 0);
	}
protected:
	std::string _s;
};

/*===========================================================================*/
/* ShaderParameterDesc                                                       */

struct ShaderParameterDesc : public DescBase
{
    typedef DescBase            Inherited;
    typedef ShaderParameterDesc Self;
    
    virtual ~ShaderParameterDesc(void);
    
    virtual void dump(std::ostream &os) const;
    
    const ShaderParameterDesc& operator=(const ShaderParameterDesc& rparam);    
    
    std::string _type;    
    std::string _valueString;
    bool        _isArray;
};



/*===========================================================================*/
/* MaterialDesc                                                              */

struct MaterialDesc : public DescBase
{
    typedef DescBase     Inherited;
    typedef MaterialDesc Self;
    
    typedef std::vector<ShaderParameterDesc> ShaderParamStore;
    typedef ShaderParamStore::iterator       ShaderParamStoreIt;
    typedef ShaderParamStore::const_iterator ShaderParamStoreConstIt;
    
    virtual ~MaterialDesc(void);

    virtual void dump(std::ostream &os) const;
    const MaterialDesc& operator=(const MaterialDesc& rparam); 
    
    std::string              _cullFace;
    
    std::string              _blendSource;
    std::string              _blendDest;
    
    std::string              _vpName;
    std::string              _fpName;

    std::vector<std::string> _texNames;
    std::vector<std::string> _texSamplerNames;
    std::vector<int        > _texSlots;
    std::vector<int        > _texSizesX;
    std::vector<int        > _texSizesY;
        
    ShaderParamStore         _shaderParams;
};

/*===========================================================================*/
/* ShaderProgramDesc                                                         */

struct ShaderProgramDesc : public DescBase
{
    typedef DescBase          Inherited;
    typedef ShaderProgramDesc Self;

    virtual ~ShaderProgramDesc(void);

    virtual void dump(std::ostream &os) const;
    const ShaderProgramDesc& operator=(const ShaderProgramDesc& rparam); 

    std::string _fileName;
    std::string _type;
};

/*===========================================================================*/
/* TextureDesc                                                               */

struct TextureDesc : public DescBase
{
    typedef DescBase    Inherited;
    typedef TextureDesc Self;
    
    virtual ~TextureDesc(void);

    virtual void dump(std::ostream &os) const;
    const TextureDesc& operator=(const TextureDesc& rparam); 
    
    std::string _fileName;
};

/*===========================================================================*/
/* KeyframeAnimationDesc                                                     */

struct KeyframeAnimationDesc : public DescBase
{
    typedef DescBase                    Inherited;
    typedef KeyframeAnimationDesc       Self;

    struct Keyframe
    {
        void dump(std::ostream &os) const;
    
        gmtl::Vec2d _cp[3];
    };
    
    // symbolic names for the control points of a keyframe
    enum CPTypeE
    {
        CP_IN  = 0,
        CP_AT  = 1,
        CP_OUT = 2
    };
    
    // symbolic names for control point time and value indices
    enum CPIndexE
    {
    	CP_TIME = 0,
    	CP_VALUE = 1
    };
    
    // symbolic names for the tracks of an animation
    enum TrackTypeE
    {
        TRACK_POS_X   = 0,
        TRACK_POS_Y   = 1,
        TRACK_POS_Z   = 2,
        
        TRACK_ROT_X   = 3,
        TRACK_ROT_Y   = 4,
        TRACK_ROT_Z   = 5,
        
        TRACK_SCALE_X = 6,
        TRACK_SCALE_Y = 7,
        TRACK_SCALE_Z = 8
    };
    
    enum AnimationStateE
    {
    	PAUSED  = 0,
    	PLAYING = 1
    };    
   
    
    static unsigned int const numTracksDesc = 9;
       
    typedef std::vector<Keyframe>         KeyframeStore;
    typedef KeyframeStore::iterator       KeyframeStoreIt;
    typedef KeyframeStore::const_iterator KeyframeStoreConstIt;

    KeyframeAnimationDesc();
    virtual ~KeyframeAnimationDesc(void);
    
    virtual void dump(std::ostream &os) const;
   
    struct TrackInfo
    {
    	std::string           _name;
    	AnimationStateE       _state;
      int 			            _lastKeyf;    //index of the last keyframe played 
      double		  	        _lastValue;
      KeyframeStore         _keyFrames;	
      std::vector<double>   _cSegment;    //current segment in the curve
    };       
    
    TrackInfo   _animTracks[numTracksDesc];
    std::string trackName(TrackTypeE);
        
    void calcSegment(unsigned int trackIndex, unsigned int startKfIndex, double tstep);
    double getValue(unsigned int trackIndex, double ttime, double tstep);  //--> gets the value from the current segment     
};
    
struct ExtrusionDesc : public DescBase
{
    typedef DescBase      Inherited;
    typedef ExtrusionDesc DescBase;

    typedef std::vector<OSG::Pnt2f>  CrossSectionCPStore;
    typedef std::vector<std::string> SpineCPNameStore;
    
    typedef std::vector<OSG::Real32> SampleStore;
    typedef std::vector<OSG::UInt32> CurveLengthStore;
    
    
    virtual ~ExtrusionDesc(void);
    
    virtual void dump(std::ostream &os) const;
    
    
    CrossSectionCPStore _crossSectionCP;
    SampleStore         _crossSectionSamples;
    
    CurveLengthStore    _spineCurveLengths;
    SpineCPNameStore    _spineCPNames;
    SampleStore         _spineSamples;
    
    OSG::Vec3f          _upVector;
};


#endif // _DESCRIPTORS_H_
