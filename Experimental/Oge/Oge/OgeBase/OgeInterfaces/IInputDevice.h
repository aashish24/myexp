
#ifndef __OGE_INTERFACES_I_INPUT_DEVICE_H__
#define __OGE_INTERFACES_I_INPUT_DEVICE_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

#include <string>

namespace Oge 
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      // Forward declaration. 
      struct IActionCallback; 
      struct IInput;

      struct IInputDevice : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IInputDevice );

        enum                          { IID = 0 };
                
        virtual void                  init() = 0; 

        virtual void                  config( const std::string& config ) = 0;

        virtual void                  update() = 0;   

        virtual IInput*               getInput( const unsigned int& index ) = 0;        
      };
    } // namespace OgeInterfaces. 
  } // namespace OgeBase.
} // namespace Oge.

#endif // __OGE_INTERFACES_I_INPUT_DEVICE_H__
