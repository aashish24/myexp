
#ifndef __VRJ_CORE__JUGGLER_CONFIG_LOADER_H__
#define __VRJ_CORE__JUGGLER_CONFIG_LOADER_H__

#include "vrj/Kernel/Kernel.h"

namespace Oge
{
  namespace OgeVrj
  {
    namespace VrjCore
    {
      struct LoadConfigFile 
      {
        void operator()( const std::string& filename ) const
        {
          // Check here if the file exits. 
          vrj::Kernel::instance()->loadConfigFile( filename );
        }
      };
    }
  }
}


#endif // __VRJ_CORE__JUGGLER_CONFIG_LOADER_H__
