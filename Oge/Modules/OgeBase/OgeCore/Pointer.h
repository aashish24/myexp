
#ifndef __OGE_CORE_POINTER_H__
#define __OGE_CORE_POINTER_H__

#include "OgeBase/OgeCore/SmartPointer.h"

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
#define OGE_SMART_PTR( class_name ) \
  Oge::OgeBase::OgeCore::SmartPointer< class_name > 

#define OGE_DELCARE_SMART_PTR( class_name ) \
  typedef OGE_SMART_PTR( class_name ) RefPtr; 
    }
  }
}

#endif // __OGE_CORE_POINTER_H__

