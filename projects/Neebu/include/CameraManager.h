
#ifndef _CAMERAMANAGER_H_
#define _CAMERAMANAGER_H_

// std library includes
#include <iosfwd>
#include <map>
#include <string>


// VRJuggler includes
#include <vpr/Util/Interval.h>

#include <gmtl/Matrix.h>

#include <Descriptors.h>
#include <CameraNavigator.h>

// forward declarations
class PathHandler;
class NamedObjectCache;
class NavigatorAdapterBase;

class CameraManager
{
  public:
    typedef std::map<std::string, KeyframeAnimationDesc>  CameraMap; 
    typedef CameraMap::iterator                           CameraMapIt;
    typedef CameraMap::const_iterator                     CameraMapConstIt;
  
    explicit CameraManager(void);
    ~CameraManager();
    
    void dump(std::ostream &os) const;  
    
    
    /*=======================================================================*/
    /* Setup                                                                 */
    /*=======================================================================*/
    void init(NavigatorAdapterBase *NavAdapter);
    
    /*=======================================================================*/
    /* Initialization                                                        */
    /*=======================================================================*/
    void readFile(std::string const &fileName);    
          
    
    /*=======================================================================*/
    /* Player                                                                */
    /*=======================================================================*/
    //load a camera; sets current transformation to keyframe 0. it won't start the animation
    void load (std::string const& tcameraName);
    void load (unsigned int cameraIndex);
    // start/stop animation
    void play_pause (vpr::Interval currTime, bool loop=true);
    // rewind animation to the start
    void rewind ();
    // fast forward to the last frame
    void fastForward ();
    // switch to free fly mode. it won't reset transformation
    void eject();
    
    // this update function to be called every frame
    void update(vpr::Interval const);
    
    // returs state of the animation player
    KeyframeAnimationDesc::AnimationStateE getState(void);
    bool isPlaying(void);
    
    vpr::Interval getStartTime();
    
  private:
    CameraMap          _camMap;
    
    vpr::Interval _mStartTime;  //time when animation was last started
    vpr::Interval _mTime;       //stores last time step
    
    CameraNavigator      *_mCamNavigator;  
    NavigatorAdapterBase *_mNavAdapter;    //The navigator adapter that will contain the camera navigator
    NavigatorBase        *_mFreeNavigator; //The other navigator to use for free fly through
    
    bool _camLoaded;
    std::string  _camName;
};


inline vpr::Interval CameraManager::getStartTime(){
	return _mStartTime;
}


inline KeyframeAnimationDesc::AnimationStateE 
	CameraManager::getState(void)
{
	return (_mCamNavigator) ? (_mCamNavigator->getState()) : KeyframeAnimationDesc::PAUSED;
}

inline bool
	CameraManager::isPlaying(void)
{
	return (_mCamNavigator) ? (_mCamNavigator->isPlaying()) : false;
}



#endif // _CAMERAMANAGER_H_
