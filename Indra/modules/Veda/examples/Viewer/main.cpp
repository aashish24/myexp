
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

#include "MyApp.h"

#include "vrj/Kernel/Kernel.h"

#if defined _MSC_VER && _DEBUG
# pragma comment( lib, "osgd.lib" )
# pragma comment( lib, "osgDBd.lib" )
# pragma comment( lib, "osgUtild.lib" )
# pragma comment( lib, "osgFXd.lib" )
# pragma comment( lib, "osgTextd.lib" )
# elif defined _MSC_VER
# pragma comment( lib, "osg.lib" )
# pragma comment( lib, "osgDB.lib" )
# pragma comment( lib, "osgUtil.lib" )
# pragma comment( lib, "osgFX.lib" )
# pragma comment( lib, "osgText.lib" )  
#endif

int main( int argc, char** argv )
{
	vrj::Kernel* kernel		= vrj::Kernel::instance();
	MyApp* application	= new MyApp( kernel, argc, argv );	
	
	// Number of argumets should be more than 1 :: Needs atleast one config file ::
	if( argc < 2 )
	{	
		std::exit(1);
	}

	for( int i = 1; i < argc; ++i )
	{
    std::cout << argv[ i ] << std::endl;
    if( std::string( argv[ i ] ) == "-c" )
    {
		  kernel->loadConfigFile( argv[ ++i ] );
    }
	}

	kernel->start();
	kernel->setApplication( application );
	kernel->waitForKernelStop();
	return 0;
}


