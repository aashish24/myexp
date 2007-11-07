
#include "boost/bind.hpp"

#include "i3dea/Vrj/AppBase.h"
#include "i3dea/Functors/GlobalDisplayFunctor.h"

#include <functional>

class Test
{
public:
	void  display2( void );
};

void Test::display2( void )
	{
	
		std::cout << "Display2:" << std::endl;
		return ;
	}

void display()
{
	std::cout << "Display:" << std::endl;
}

int main()
{
	Test testApp;
			
	//i3dea::vrj::setDisplayFunc( boost::bind( &Test::display2, &testApp ) );
  i3dea::vrj::setDisplayFunc( &display );

	i3dea::vrj::AppBase::instance().run();

	i3dea::vrj::AppBase::exit();
}