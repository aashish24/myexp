

#include "MyApp.h"

#include <vrj/Kernel/Kernel.h>

int main( int argc, char* argv[] )
{
	vrj::Kernel* kernel		= vrj::Kernel::instance();
	MyApp* application	= new MyApp(kernel, argc, argv);	
	
	// Number of argumets should be more than 1 :: Needs atleast one config file ::
	if( argc < 2 )
	{
		std::cerr << " Test: " << std::endl;
		std::exit(1);
	}

	for( int i = 1; i < argc; ++i )
	{
		kernel->loadConfigFile( argv[i] );
	}

	kernel->start();
	kernel->setApplication( application );
	kernel->waitForKernelStop();
	return 0;
}


