
// gmtl includes
#include <gmtl/gmtl.h>
#include <gmtl/AxisAngle.h>

#include <CameraNavigator.h>

#include <AnimationTools.h>


void Euler2Matrix(float angle_x, float angle_y, float angle_z, float mat[16]);


    CameraNavigator::CameraNavigator(vrj::App *pApp)
    
    : Inherited(pApp),
      mPos(gmtl::Point3d(0,0,0)),
      mRot(gmtl::EulerAngleZYXd(0,0,0)),
      mScale(gmtl::Vec3d(1,1,1)),
      mAnimDesc(NULL),
      _mState(KeyframeAnimationDesc::PAUSED),
      _justloaded(false),
      _timestep(0.00001)
{
    _mTotal.set(0, vpr::Interval::Sec);
    
}


    CameraNavigator::~CameraNavigator(void)
{
    // nothing to do
}

//note! eye position assumed to be in the origin for now
void 
	CameraNavigator::initialize()
{
	if(getInitialized())
	        return;
	    
	    Inherited::initialize();	
}
    

void
    CameraNavigator::navigate(
        gmtl::Matrix44f const &matrix,
        gmtl::Matrix44f       &newMatrix)
{
    if(getEnabled() == false)
        return;
    
    Inherited::navigate(matrix, newMatrix);   
    
    if (_mState==KeyframeAnimationDesc::PLAYING){
    	updateAnim(_mTotal);      
    }
    
    // set translation and rotation parts
//    std::cout << "*************** CAMERA NAV: POS: " << mPos << ", ROT " << mRot << "\n"
//              << "*** time: " << (_mTime - _mStartTime).secf() << std::endl;
    
   // if ( (_mState==KeyframeAnimationDesc::PLAYING) || (_justloaded) ) { 
	    //trying to see if the near keyframe problem is a precision-related one..... so everything uses double
	    gmtl::Point3f        tPos(static_cast<float>(mPos[0]), static_cast<float>(mPos[1]), static_cast<float>(mPos[2]));
	    gmtl::EulerAngleZYXf tRot(static_cast<float>(mRot[0]), static_cast<float>(mRot[1]), static_cast<float>(mRot[2]));    
	    
	    //gmtl::setTrans(newMatrix, mPos);
	    //gmtl::setRot(newMatrix, mRot);
	    
	    gmtl::setTrans(newMatrix, tPos);
	    gmtl::setRot(newMatrix, tRot);
	    gmtl::invert(newMatrix);
	    
	    //_justloaded=false;
	    //std::cout << " ************** PLAYING OR JUST LOADED  **** " << std::endl;
    //}

    	
}


void CameraNavigator::setToKeyframeI(unsigned int const keyIndex)
{
	if (mAnimDesc){
		double tvalues[KeyframeAnimationDesc::numTracks];

		//Only do translation and rotation animation
		for (unsigned int i = 0; i < KeyframeAnimationDesc::TRACK_SCALE_X; i++){			
			tvalues[i] = 0;								
			
			KeyframeAnimationDesc::TrackInfo& ttrack = mAnimDesc->_animTracks[i];
			KeyframeAnimationDesc::Keyframe kf = ttrack._keyFrames[keyIndex];
			tvalues[i] = kf._cp[KeyframeAnimationDesc::CP_AT][1];
			
			ttrack._lastValue = tvalues[i];
			ttrack._lastKeyf  = keyIndex;
			
		}
				
		mPos   = gmtl::Point3d(tvalues[KeyframeAnimationDesc::TRACK_POS_X],
				       tvalues[KeyframeAnimationDesc::TRACK_POS_Y],
				       tvalues[KeyframeAnimationDesc::TRACK_POS_Z]);
		mRot   = gmtl::EulerAngleZYXd(gmtl::Math::deg2Rad(tvalues[KeyframeAnimationDesc::TRACK_ROT_Z]),
					  gmtl::Math::deg2Rad(tvalues[KeyframeAnimationDesc::TRACK_ROT_Y]),
					  gmtl::Math::deg2Rad(tvalues[KeyframeAnimationDesc::TRACK_ROT_X]));		
	
	}
	else
		vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
			<< "CameraNavigator::setToKeyframeI: Animation description is NULL "		            
		    << vprDEBUG_FLUSH; 
	
	
}


void 
	CameraNavigator::setToKeyframe(double tTime)
{	
	
	if (mAnimDesc){
		double tvalues[KeyframeAnimationDesc::numTracks];

		//Only do translation and rotation animation
		for (unsigned int i = 0; i < KeyframeAnimationDesc::TRACK_SCALE_X; i++){			
			tvalues[i] = 0;			
						
			bool found = false;
			unsigned int j = 0;
			int tkeyIndex = KEYF_NOTYET;	
			
			KeyframeAnimationDesc::TrackInfo& ttrack = mAnimDesc->_animTracks[i];
			
			while ( (j < ttrack._keyFrames.size()) && !found ){
				KeyframeAnimationDesc::Keyframe kf = ttrack._keyFrames[j];
				double kfTime = kf._cp[KeyframeAnimationDesc::CP_AT][0];
				if ((j==0) && (kfTime > tTime)){
					tvalues[i] = kf._cp[KeyframeAnimationDesc::CP_AT][1];
					found = true;
					tkeyIndex = KEYF_NOTYET;
				}
						
				else if ((j==ttrack._keyFrames.size()-1) && (kfTime < tTime))  {
					tvalues[i] = kf._cp[KeyframeAnimationDesc::CP_AT][1];
					found = true;
					tkeyIndex = KEYF_FINISHED;
				}
				
				else if (fabs(kfTime - tTime) <= std::numeric_limits<double>::epsilon()){
					tvalues[i] = kf._cp[KeyframeAnimationDesc::CP_AT][1];
					found = true;
					tkeyIndex = j;
				}
				
				j++;					
			}
			
			//hack for ROT_Z -- multiply by -1
			if (i==KeyframeAnimationDesc::TRACK_ROT_Z){
				//tvalues[i] *= (-1.0f);
			}
			
			ttrack._lastValue = tvalues[i];
			ttrack._lastKeyf  = tkeyIndex;
			
		}
				
		mPos   = gmtl::Point3d(tvalues[KeyframeAnimationDesc::TRACK_POS_X],
				   tvalues[KeyframeAnimationDesc::TRACK_POS_Y],
				   tvalues[KeyframeAnimationDesc::TRACK_POS_Z]);
		mRot   = gmtl::EulerAngleZYXd(gmtl::Math::deg2Rad(tvalues[KeyframeAnimationDesc::TRACK_ROT_Z]),
					  gmtl::Math::deg2Rad(tvalues[KeyframeAnimationDesc::TRACK_ROT_Y]),
					  gmtl::Math::deg2Rad(tvalues[KeyframeAnimationDesc::TRACK_ROT_X]));		
	}
	else
		vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
			<< "CameraNavigator::setToTime: Animation description is NULL "		            
		    << vprDEBUG_FLUSH;        
}



int CameraNavigator::findNextK(KeyframeAnimationDesc::KeyframeStore const& ttrack, unsigned int startKey, double tTime)
{
	
	double time0 = ttrack[startKey]._cp[KeyframeAnimationDesc::CP_AT][0];
	if (tTime < time0)
		return KEYF_NOTYET;
	
	bool found = false;	
	unsigned int start = startKey;	
	while ( ((start+1) < ttrack.size()) && !found ) {
		float time1 = ttrack[start+1]._cp[KeyframeAnimationDesc::CP_AT][0];
		if (tTime <= time1){
			found = true;
		}
		else {
			start++;
		}		
	}
	if (found) return start;
	else return KEYF_FINISHED;
	
}


// called by updateAnim
// assumes player has been started  (_mState == PLAYING)
// tdiff is time since animation started (minus paused intervals)
void CameraNavigator::updateTrack(unsigned int trackIndex, double tdiff)
{
	KeyframeAnimationDesc::KeyframeStore& ttrack   = mAnimDesc->_animTracks[trackIndex]._keyFrames;
	
	int lastKeyf = mAnimDesc->_animTracks[trackIndex]._lastKeyf;
	int nextKeyf;  

	if (lastKeyf < 0)
		nextKeyf = findNextK(ttrack, 0, tdiff);
	else
		nextKeyf = findNextK(ttrack, lastKeyf, tdiff);
	

	//evaluate
	if (nextKeyf >= 0){
		
		/************************ pre calc segments
		
		if (lastKeyf != nextKeyf){
			mAnimDesc->calcSegment(trackIndex, nextKeyf, _timestep);
			std::cout << " segment calculated for track " << trackIndex << ", lastkey" << lastKeyf << ", next " << nextKeyf << std::endl;
		}
		//normalize time first
		double t = tnormalize(tdiff, 
				ttrack[nextKeyf]._cp[KeyframeAnimationDesc::CP_AT][0], 
			        ttrack[nextKeyf+1]._cp[KeyframeAnimationDesc::CP_AT][0]);
		double res = mAnimDesc->getValue(trackIndex, t, _timestep);
		
		*******************************/
		
		
		//normalize time first
		double t = tnormalize(tdiff, 
				ttrack[nextKeyf]._cp[KeyframeAnimationDesc::CP_AT][0], 
			        ttrack[nextKeyf+1]._cp[KeyframeAnimationDesc::CP_AT][0]);
		
		//call bezier evaluation function		
		double res = fbezierEval(t, 
				ttrack[nextKeyf  ]._cp[KeyframeAnimationDesc::CP_AT ][1], 
				ttrack[nextKeyf  ]._cp[KeyframeAnimationDesc::CP_OUT][1],
				ttrack[nextKeyf+1]._cp[KeyframeAnimationDesc::CP_IN ][1],
				ttrack[nextKeyf+1]._cp[KeyframeAnimationDesc::CP_AT ][1]);
			
		
		
		//update state info
		mAnimDesc->_animTracks[trackIndex]._lastKeyf  = nextKeyf;
		mAnimDesc->_animTracks[trackIndex]._lastValue = res;
		mAnimDesc->_animTracks[trackIndex]._state     = KeyframeAnimationDesc::PLAYING;
	}
	else if (nextKeyf == KEYF_NOTYET)  //animation was triggered, but not time yet to play past keyframe 0
		mAnimDesc->_animTracks[trackIndex]._state     = KeyframeAnimationDesc::PLAYING;
	else //time is past last keyframe, got to stop animation
		mAnimDesc->_animTracks[trackIndex]._state     = KeyframeAnimationDesc::PAUSED;
	
}


//updateAnim
// assumes player has been started  (_mState == PLAYING)
// tdiff is time since animation started (minus paused intervals)
void 
	CameraNavigator::updateAnim(vpr::Interval const tdiff)
{
	
	std::vector<double> tvalues;	
	bool still_playing = false;
	//update each track
	for(unsigned int i = 0; i< KeyframeAnimationDesc::TRACK_SCALE_X; i++){
		updateTrack(i, tdiff.secd());
		
		// hack! ---  multiply by -1 for mRot[2] = TRACK_ROT_Z
		//if ( (i==KeyframeAnimationDesc::TRACK_ROT_Z) && (mAnimDesc->_animTracks[i]._state == KeyframeAnimationDesc::PLAYING) ){
			//mAnimDesc->_animTracks[i]._lastValue *= (-1.0f);
		//}
		
		tvalues.push_back(mAnimDesc->_animTracks[i]._lastValue);
		if (mAnimDesc->_animTracks[i]._state == KeyframeAnimationDesc::PLAYING)
			still_playing = true;
	}
	
	//now apply new values
	mPos   = gmtl::Point3d(tvalues[KeyframeAnimationDesc::TRACK_POS_X],
			   tvalues[KeyframeAnimationDesc::TRACK_POS_Y],
			   tvalues[KeyframeAnimationDesc::TRACK_POS_Z]);
	mRot   = gmtl::EulerAngleZYXd(gmtl::Math::deg2Rad(tvalues[KeyframeAnimationDesc::TRACK_ROT_Z]),
				  gmtl::Math::deg2Rad(tvalues[KeyframeAnimationDesc::TRACK_ROT_Y]),
				  gmtl::Math::deg2Rad(tvalues[KeyframeAnimationDesc::TRACK_ROT_X]));
	
	//rewind and play again next frame if looping is set
	if ( (!still_playing) && (_loop) ){
		_mState = KeyframeAnimationDesc::PLAYING;
		rewind();
	}
	else
		_mState = still_playing ?  KeyframeAnimationDesc::PLAYING : KeyframeAnimationDesc::PAUSED;
		
}


void CameraNavigator::rewind(){
	setToKeyframeI(0);	
	_mTotal.set(0, vpr::Interval::Sec);
}




void Euler2Matrix(float angle_x, float angle_y, float angle_z, float mat[16]){
    float A       = cos(angle_x);
    float B       = sin(angle_x);
    float C       = cos(angle_y);
    float D       = sin(angle_y);
    float E       = cos(angle_z);
    float F       = sin(angle_z);

    float AD      =   A * D;
    float BD      =   B * D;

    mat[0]  =   C * E;
    mat[4]  =  -C * F;
    mat[8]  =  -D;
    mat[1]  = -BD * E + A * F;
    mat[5]  =  BD * F + A * E;
    mat[9]  =  -B * C;
    mat[2]  =  AD * E + B * F;
    mat[6]  = -AD * F + B * E;
    mat[10] =   A * C;

    mat[12]  =  mat[13] = mat[11] = mat[3] = mat[7] = mat[11] = 0;
    mat[15] =  1;
}


