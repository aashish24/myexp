
#ifndef _CAMERANAVIGATOR_H_
#define _CAMERANAVIGATOR_H_

#include <NavigatorBase.h>

// gmtl includes
#include <gmtl/EulerAngle.h>
#include <gmtl/Point.h>
#include <gmtl/Vec.h>


// vpr includes
#include <vpr/Util/Interval.h>

#include <Descriptors.h>

class CameraNavigator : public NavigatorBase
{
  public:
    typedef NavigatorBase    Inherited;
    typedef CameraNavigator Self;
    
    /*=======================================================================*/
    /* Construction/Destruction                                              */
    
             CameraNavigator(vrj::App *pApp);
    virtual ~CameraNavigator(void);
    
    /*=======================================================================*/
    /* Initialization                                                        */
    virtual void initialize(void);
    
    
    /*=======================================================================*/
    /* Navigation                                                            */
    
    void                     setTranslation(gmtl::Point3d const &       pos  );
    gmtl::Point3d const &    getTranslation(void) const;
    void                     setRotation   (gmtl::EulerAngleZYXd const &rot  );
    gmtl::EulerAngleZYXd const &getRotation(void) const;
    void                     setScale      (gmtl::Vec3d const &         scale);
    gmtl::Vec3d const &      getScale      (void) const;
    
    virtual void navigate(gmtl::Matrix44f const &matrix,
                          gmtl::Matrix44f       &newMatrix);
    
    void load(KeyframeAnimationDesc& kfDesc);
    void setToKeyframe(double tTime);
    void play_pause(vpr::Interval currTime, bool loop=true);
    void rewind(void);
    void fastForward(void);
    bool isPlaying(void);
    KeyframeAnimationDesc::AnimationStateE getState(void);
    bool getLoopSetting();
    
    //This one to be called every frame. can be called even if animation is not playing.
    void updateTime(vpr::Interval const tTime);
    
    
  private:
    gmtl::Point3d        mPos;
    gmtl::EulerAngleZYXd mRot;
    gmtl::Vec3d          mScale;
    
    bool _loop;
        
    KeyframeAnimationDesc*  mAnimDesc; 
    vpr::Interval _mStartTime;  //time when animation was last started
    vpr::Interval _mTime;       //current time
    vpr::Interval _mPrevt;      //previous frame's time  
    vpr::Interval _mTotal;      //this one keeps track of current "time" in the whole animation 
    KeyframeAnimationDesc::AnimationStateE  _mState;       
    
    bool _justloaded; //used to avoid setting matrices when it's paused
    
    int findNextK(KeyframeAnimationDesc::KeyframeStore const& ttrack, unsigned int startKey, double tTime);
    void updateTrack(unsigned int trackIndex, double tdiff);
    void updateAnim(vpr::Interval const tdiff);
    
    //sets everybody to the specific keyframe index 
    void setToKeyframeI(unsigned int const keyIndex);
    
    
    //enum for out of boundaries index keys
    enum keyIndexE {
    	KEYF_FINISHED = -2,  //means current time is past the last keyframe
    	KEYF_NOTYET   = -1   //means current time is not yet first keyframe
    };
    
    double _timestep;
    
};

inline void CameraNavigator::load(KeyframeAnimationDesc& kfDesc){
	mAnimDesc = &kfDesc;
	if (_mTotal.secf() > 0){  //means camera was previously ejected
		//nothing, actually.....
	}
	
	else{
		setToKeyframeI(0);
		_mTotal.set(0, vpr::Interval::Sec);		
	}
	_justloaded = true;
	
	/*
	for (unsigned int i=0; i< mAnimDesc->numTracks; i++){
		mAnimDesc->calcSegment(i, 0 , _timestep);
	}
	*/
	
	
}

inline void CameraNavigator::updateTime(vpr::Interval const tTime){
	if (_mState == KeyframeAnimationDesc::PLAYING){
		_mPrevt = _mTime;
		_mTime  =  tTime;
		_mTotal += (_mTime - _mPrevt);
	}
}

inline void CameraNavigator::play_pause(vpr::Interval currTime, bool loop){
	_mState = (_mState==KeyframeAnimationDesc::PAUSED) ? KeyframeAnimationDesc::PLAYING : KeyframeAnimationDesc::PAUSED;
	
	//if (_mState == KeyframeAnimationDesc::PLAYING){
	//	_mStartTime = currTime;		
		_mTime = currTime;
		_loop = loop;
	//}
	
}

inline bool CameraNavigator::isPlaying(void){
	return (_mState == KeyframeAnimationDesc::PLAYING);
}

inline bool CameraNavigator::getLoopSetting(){
	return _loop;
}


inline KeyframeAnimationDesc::AnimationStateE CameraNavigator::getState(void){
	return _mState;
}

inline void
	CameraNavigator::setTranslation(gmtl::Point3d const &pos)
{
    mPos = pos;
}

inline gmtl::Point3d const &
	CameraNavigator::getTranslation(void) const
{
    return mPos;
}

inline void
	CameraNavigator::setRotation(gmtl::EulerAngleZYXd const &rot)
{
    mRot = rot;
}

inline gmtl::EulerAngleZYXd const &
	CameraNavigator::getRotation(void) const
{
    return mRot;
}

inline void
	CameraNavigator::setScale(gmtl::Vec3d const &scale)
{
    mScale = scale;
}

inline gmtl::Vec3d const &
	CameraNavigator::getScale(void) const
{
    return mScale;
}

#endif // _CAMERANAVIGATOR_H_

