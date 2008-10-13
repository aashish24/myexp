
#include <Descriptors.h>

#include <ostream>

#include <AnimationTools.h>

//unsigned int const KeyframeAnimationDesc::numTracks = 9;

/*===========================================================================*/
/* DescBase                                                                  */

    DescBase::~DescBase(void)
{
    // nothing to do
}

void
    DescBase::dump(std::ostream &os) const
{
    os << "name [" << _name << "]";
}

/*===========================================================================*/
/* ShaderParameterDesc                                                       */

    ShaderParameterDesc::~ShaderParameterDesc(void)
{
    // nothing to do
}

void
    ShaderParameterDesc::dump(std::ostream &os) const
{
    os << "ShaderParameterDesc: ";

    Inherited::dump(os);
    
    os <<   " type ["        << _type 
       <<  "] valueString [" << _valueString
       <<  "] array ["       << _isArray
       << "]";
}


const ShaderParameterDesc& ShaderParameterDesc::operator=(const ShaderParameterDesc& rparam){
	_name = rparam._name;
	_type = rparam._type;
	_valueString = rparam._valueString;
	_isArray = rparam._isArray;
	return (*this);
}


/*===========================================================================*/
/* MaterialDesc                                                              */

    MaterialDesc::~MaterialDesc(void)
{
    // nothing to do
}

void
    MaterialDesc::dump(std::ostream &os) const
{
    os << "MaterialDesc: ";

    Inherited::dump(os);
    
    os <<  " cullFace ["    << _cullFace
       << "] blendSource [" << _blendSource
       << "] blendDest ["   << _blendDest
       << "] vpName ["      << _vpName
       << "] fpName ["      << _fpName << "]";
       
    std::size_t numTex = _texNames.size();
    
    for(std::size_t i = 0; i < numTex; ++i)
    {
        os <<  " texName ["    << _texNames[i]
           << "] texSampler [" << _texSamplerNames[i]
           << "] texSlot ["    << _texSlots[i]
           << "] texSizeX ["   << _texSizesX[i]
           << "] texSizeY ["   << _texSizesY[i]
           << "]";
    }
    
    std::size_t numParam = _shaderParams.size();
    
    for(std::size_t i = 0; i < numParam; ++i)
    {
        os << " param [" << i << "] ";
        _shaderParams[i].dump(os);
    }
}


const MaterialDesc& MaterialDesc::operator=(const MaterialDesc& rparam){
	_name            = rparam._name;
    _cullFace        = rparam._cullFace;    
    _blendSource     = rparam._blendSource;
    _blendDest       = rparam._blendDest;    
    _vpName          = rparam._vpName;
    _fpName          = rparam._fpName;
    _texNames        = rparam._texNames;
    _texSamplerNames = rparam._texSamplerNames;
    _texSlots        = rparam._texSlots;
    _texSizesX       = rparam._texSizesX;
    _texSizesY       = rparam._texSizesY;    
    _shaderParams    = rparam._shaderParams;
    
    return (*this);
	
}


/*===========================================================================*/
/* ShaderDesc                                                                */

    ShaderProgramDesc::~ShaderProgramDesc(void)
{
    // nothing to do
}

void
    ShaderProgramDesc::dump(std::ostream &os) const
{
    os << "ShaderProgramDesc: ";
    
    Inherited::dump(os);
    
    os <<   "fileName [" << _fileName 
       << "] type ["     << _type
       << "]";
}

const ShaderProgramDesc& 
	ShaderProgramDesc::operator=(const ShaderProgramDesc& rparam)
{
	_name     = rparam._name;
	_fileName = rparam._fileName;
	_type     = rparam._type;
	
	return (*this);
}

/*===========================================================================*/
/* TextureDesc                                                               */

    TextureDesc::~TextureDesc(void)
{
    // nothing to do
}

void
    TextureDesc::dump(std::ostream &os) const
{
    os << "TextureDesc: ";
    
    Inherited::dump(os);
    
    os << " fileName [" << _fileName << "]";
}


const TextureDesc& 
	TextureDesc::operator=(const TextureDesc& rparam)
{
	_name     = rparam._name;
	_fileName = rparam._fileName;
	
	return (*this);
}

/*===========================================================================*/
/* KeyframeAnimationDesc                                                     */


void
    KeyframeAnimationDesc::Keyframe::dump(std::ostream &os) const
{
    os << " time [" << _cp[CP_AT][0]  << "] --"
       <<      " [" << _cp[CP_IN][0]  << "][" << _cp[CP_IN][1]
       <<     "] [" << _cp[CP_AT][0]  << "][" << _cp[CP_AT][1]
       <<     "] [" << _cp[CP_OUT][0] << "][" << _cp[CP_OUT][1]
       << "]";
}

	KeyframeAnimationDesc::KeyframeAnimationDesc(void)
{
	for (unsigned int i=0; i < numTracks; i++){
		TrackInfo& ttrack =  _animTracks[i];
		ttrack._name = trackName(static_cast<TrackTypeE>(i));
		ttrack._lastKeyf = -1;
		ttrack._state = PAUSED;
	}
}


    KeyframeAnimationDesc::~KeyframeAnimationDesc(void)
{
    // nothing to do
}
    
void
    KeyframeAnimationDesc::dump(std::ostream &os) const
{
    os << "AnimationDesc: ";
    
    Inherited::dump(os);
    
    for (unsigned int i=0; i < numTracks; i++){
    	const TrackInfo& ttrack =  _animTracks[i];
    	os << std::endl << ttrack._name << std::endl;
    	for (unsigned int j=0; j < ttrack._keyFrames.size(); j++){
    		os << " ";
    		ttrack._keyFrames[j].dump(os);
    		os << std::endl;
    	}
    }
}

std::string 
	KeyframeAnimationDesc::trackName(TrackTypeE ttype) 
{
	switch (ttype){
	case TRACK_POS_X:
		return std::string("POS_X");
	case TRACK_POS_Y:
		return std::string("POS_Y");
	case TRACK_POS_Z:
		return std::string("POS_Z");
	case TRACK_ROT_X:
		return std::string("ROT_X");
	case TRACK_ROT_Y:
		return std::string("ROT_Y");
	case TRACK_ROT_Z:
		return std::string("ROT_Z");
	case TRACK_SCALE_X:
		return std::string("SCALE_X");
	case TRACK_SCALE_Y:
		return std::string("SCALE_Y");
	case TRACK_SCALE_Z:
		return std::string("SCALE_Z");
	default:
		return std::string("UNKNOWN_TRACK_TYPE");
	}	
}

void KeyframeAnimationDesc::calcSegment(unsigned int trackIndex, unsigned int startKfIndex, double tstep){
	Keyframe kfstart = _animTracks[trackIndex]._keyFrames[startKfIndex];
	Keyframe kfend   = _animTracks[trackIndex]._keyFrames[startKfIndex+1];
	
	_animTracks[trackIndex]._cSegment.clear();
	_animTracks[trackIndex]._cSegment = calcBezier(tstep, kfstart._cp[CP_AT][1], kfstart._cp[CP_OUT][1],
													kfend._cp[CP_IN][1],   kfend._cp[CP_AT][1]);
}

double KeyframeAnimationDesc::getValue(unsigned int trackIndex, double ttime, double tstep){
	
	TrackInfo ttrack = _animTracks[trackIndex];
	unsigned int i = static_cast<unsigned int>(gmtl::Math::round (ttime / tstep)) ;
	
	//just in case
	if (i < ttrack._cSegment.size())
		return ttrack._cSegment[i];
	else{
		std::cout << "KeyframeAnimationDesc::getValue : time is out of boundaries!!!! **************** " << ttime << " , " << ttrack._cSegment.size() << 
		 " , " << i << ", " << ttrack._lastKeyf << " on track " << trackIndex << std::endl;
		return 0;
	}
				
}



/*===========================================================================*/
/* ExtrusionDesc                                                             */

    ExtrusionDesc::~ExtrusionDesc(void)
{
    // nothing to do
}

void
    ExtrusionDesc::dump(std::ostream &os) const
{
    os << "Extrusion: ";
    
    Inherited::dump(os);
    
    os << "\ncross section cp\n";
    
    for(unsigned int i = 0; i < _crossSectionCP.size(); ++i)
    {
        os << " <" << _crossSectionCP[i] << ">,";
    }
    
    os << "\ncross section samples\n";
    
    for(unsigned int i = 0; i < _crossSectionSamples.size(); ++i)
    {
        os << " " << _crossSectionSamples[i] << ",";
    }
    
    os << "\nspine curve lengths\n";
    
    for(unsigned int i = 0; i < _spineCurveLengths.size(); ++i)
    {
        os << " " << _spineCurveLengths[i] << ",";
    }
    
    os << "\nspine cp\n";
    
    for(unsigned int i = 0; i < _spineCPNames.size(); ++i)
    {
        os << " " << _spineCPNames[i] << ",";
    }
    
    os << "\nspine samples\n";
    
    for(unsigned int i = 0; i < _spineSamples.size(); ++i)
    {
        os << " " << _spineSamples[i] << ",";
    }
    
    os << "\nup vector " << _upVector << "\n";
}
