
#ifndef __MSG_UTIL_GEOMETRY_FUNCS_H__
#define __MSG_UTIL_GEOMETRY_FUNCS_H__

#include "MirageCore/Referenced.h"

namespace Mirage
{
  namespace MirageCore
  {
    class Geometry;
  }

  namespace MirageUtil
  {
    class MSG_EXPORT GeometryFuncs : public Mirage::MirageCore::Referenced
    {
      public:

        static void generateNormals( Mirage::MirageCore::Geometry* geom );

        static void generateTBNs( Mirage::MirageCore::Geometry* geom ); 
    };
  }
}

#endif // __MSG_UTIL_GEOMETRY_FUNCS_H__
