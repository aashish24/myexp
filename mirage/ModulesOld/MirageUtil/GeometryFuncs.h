
#ifndef __MSG_UTIL_GEOMETRY_FUNCS_H__
#define __MSG_UTIL_GEOMETRY_FUNCS_H__

#include "MsgCore/Referenced.h"

namespace Msg
{
  namespace MsgCore
  {
    class Geometry;
  }

  namespace MsgUtil
  {
    class MSG_EXPORT GeometryFuncs : public Msg::MsgCore::Referenced
    {
      public:

        static void generateNormals( Msg::MsgCore::Geometry* geom );

        static void generateTBNs( Msg::MsgCore::Geometry* geom ); 
    };
  }
}

#endif // __MSG_UTIL_GEOMETRY_FUNCS_H__
