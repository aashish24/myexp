
#include "OpenSGNav.h"

#include "vrj/Kernel/Kernel.h"

int main(int argc, char* argv[])
{
   vrj::Kernel* kernel = vrj::Kernel::instance();
   OpenSGNav* application = new OpenSGNav(kernel);

#if ! defined(VRJ_USE_COCOA)
   if ( argc <= 2 )
   {
      std::cout << "\n\nUsage: " << argv[0]
                << " modelname vjconfigfile[0] vjconfigfile[1] ... vjconfigfile[n]\n"
                << std::flush;
      exit(1);
   }
#endif

   application->setModelFileName(std::string(argv[1]));

   // Load any config files specified on the command line
   for ( int i = 2; i < argc; ++i )
   {
      kernel->loadConfigFile(argv[i]);
   }
    
   kernel->start();
   kernel->setApplication(application);
   kernel->waitForKernelStop();

   delete application;

   return 0;
}
