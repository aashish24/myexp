
#ifndef __NEIV_POINTER_POINTER_H__
#define __NEIV_POINTER_POINTER_H__

// This should be the first include. 
#include "Neiv/NeivConfig.h"

#include "Neiv/Pointer/SmartPointer.h"

namespace Neiv
{
  namespace Pointer
  {
  
    #define NEIV_SMART_PTR( class_name ) \
      Neiv::Pointer::SmartPointer< class_name > 

    #define NEIV_DELCARE_SMART_PTR( class_name ) \
      typedef NEIV_SMART_PTR( class_name ) RefPtr; 
  }
}

#endif // __NEIV_POINTER_POINTER_H__