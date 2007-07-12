
#include "VrjApp.h"

#include "vrj/Kernel/Kernel.h"

int main( int argc, char* argv[] )
{
	vrj::Kernel* kernel		= vrj::Kernel::instance();
	VrjApp* application	= new VrjApp(kernel, argc, argv);	
	
	// Number of argumets should be more than 1.
	if( argc < 2 )
	{	
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



