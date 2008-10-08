#include <iostream>
#include <string>

#include <Sunoh.h>


int main( int argc, char* argv[] )
{
	float x, y, z;
	float m11, m12, m13, m21, m22, m23, m31, m32, m33; 


	Sunoh mSuno;
	mSuno.setAPI("OpenAL");
	mSuno.addSound("../data/Water.wav", "Water");
	mSuno.setPosition("Water", 0.0, 0.0, 0.0);
	mSuno.playSound("Water", -1);

	//mSuno.removeSound("Water");

	while(1)
	{
		mSuno.update();
		static float pos = -5.0;
		mSuno.setListenerPosition(pos, 0.0, 0.0);
		Sleep(1000);
		pos = pos + 1.0;

		mSuno.getListenerPosition(x, y, z);
		mSuno.getListenerOrientation(m11, m12, m13, m21, m22, m23, m31, m32, m33);
		

		std::cerr << " L position: "    << x << " " << y << " " << z << std::endl;
		std::cerr << " L orientation: " << m11 << " " << m12 << " " << m13 << std::endl;
		std::cerr << " L orientation: " << m21 << " " << m22 << " " << m23 << std::endl;
		std::cerr << " L orientation: " << m31 << " " << m32 << " " << m33 << std::endl;

	}

	return 1;
}
