


#include <Sunoh.h>

void Sunoh::setAPI(const std::string& api)
{
	snx::sonix::instance()->changeAPI( api );
}

void Sunoh::addSound(const std::string& filename, const std::string& soundID, DataSource dataSource)
{
   snx::SoundInfo soundInfo;
   soundInfo.filename = filename;   
   soundInfo.datasource = dataSource;
   
   snx::SoundHandle soundHandle;
   soundHandle.init(soundID);
   soundHandle.configure(soundInfo);

   mSoundHandleMap[soundID] = soundHandle;
}

void Sunoh::removeSound(const std::string& soundID)
{
	mSoundHandleMap[soundID].remove();	
}

void Sunoh::playSound(const std::string& soundID, const int& loopMode)
{
	mSoundHandleMap[soundID].trigger(loopMode);
}

void Sunoh::pauseSound(const std::string& soundID)
{
	mSoundHandleMap[soundID].pause();
}

void Sunoh::stopSound(const std::string& soundID)
{
	mSoundHandleMap[soundID].stop();
}


void Sunoh::setPosition(const std::string& soundID, 
						const float& x, 
						const float& y, 
						const float& z)
{
	mSoundHandleMap[soundID].setPosition(x, y, z);
}
	
void Sunoh::getPosition(const std::string& soundID,
						float& x, float& y, float& z)
{
	return mSoundHandleMap[soundID].getPosition(x, y, z);
}

void Sunoh::setListenerPosition(const float& x, const float& y, const float& z)
{
	gmtl::Matrix44f posMat;
	posMat.set(1.0, 0.0, 0.0, x,
			   0.0, 1.0, 0.0, y,
			   0.0, 0.0, 1.0, z,
			   0.0, 0.0, 0.0, 1);

	snx::sonix::instance()->setListenerPosition(posMat);
}

void Sunoh::getListenerPosition(float& x, float& y, float& z)
{
	gmtl::Matrix44f mat;
	snx::sonix::instance()->getListenerPosition(mat);

	x = mat(0, 3);
	y = mat(1, 3);
	z = mat(2, 3);
}

void Sunoh::setListenerOrientation(const float& m11, const float& m12, const float& m13,
								   const float& m21, const float& m22, const float& m23,
								   const float& m31, const float& m32, const float& m33)
{
	float x, y, z;
	gmtl::Matrix44f posMat;

	getListenerPosition(x, y, z);	
	
	posMat.set(m11, m12, m13, x,
			   m21, m22, m23, y,
			   m31, m32, m33, z,
			   0.0, 0.0, 0.0, 1);
}

void Sunoh::getListenerOrientation(float& m11,  float& m12,  float& m13,
								   float& m21,  float& m22,  float& m23,
								   float& m31,  float& m32,  float& m33)
{
	gmtl::Matrix44f mat;

	snx::sonix::instance()->getListenerPosition(mat);
	
	m11 = mat(0, 0); m12 = mat(0, 1); m13 = mat(0, 2);
	m21 = mat(1, 0); m22 = mat(1, 1); m23 = mat(1, 2);
	m31 = mat(2, 0); m32 = mat(2, 1); m33 = mat(2, 2);
}

void Sunoh::update()
{
	float cTime = clock();
	float timeDelta = (cTime - mLastTime)/(CLOCKS_PER_SEC * 1000);
	mLastTime = cTime;
	snx::sonix::instance()->step( timeDelta ); 	
}