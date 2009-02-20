


#ifndef _SUNOH_H_
#define _SUNOH_H_

/// C++ includes. 
#include <time.h>

/// STL includes. 
#include <deque>

/// Sonix includes. 
#include <snx/sonix.h>    
#include <snx/SoundHandle.h>

/// Sunoh includes. 
#include <Def.h>

class Sunoh
{
	public:
		Sunoh()
		{
			mLastTime = clock();
		}

		~Sunoh(){;}

		void setAPI(const std::string& api_name);

		void addSound(
			const std::string& filename, 
			const std::string& soundID,
			DataSource dataSource=SoundInfo::FILESYSTEM);

		void removeSound(const std::string& soundID);

		void playSound(const std::string& soundID, const int& loopMode);

        void stopSound(const std::string& soundID);

		void pauseSound(const std::string& soundID);

        void setPosition(const std::string& soundID, 
						 const float& x, const float& y, const float& z);
	
		void getPosition(const std::string& soundID, 
						 float& x, float& y, float& z);

		void setListenerPosition(const float& x, const float& y, const float& z);

		void getListenerPosition(float& x, float& y, float& z);

		void setListenerOrientation(const float& m11, const float& m12, const float& m13,
									const float& m21, const float& m22, const float& m23,
									const float& m31, const float& m32, const float& m33);

		void getListenerOrientation(float& m11,  float& m12,  float& m13,
									float& m21,  float& m22,  float& m23,
									float& m31,  float& m32,  float& m33);

		void update();

	private:                          
		long double mLastTime;

		std::map< std::string, snx::SoundHandle > mSoundHandleMap;
};

#endif /// _SUNOH_H_
