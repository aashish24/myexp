
#ifndef __OGE_INTERFACES_I_INPUT_DEVICE_H__
#define __OGE_INTERFACES_I_INPUT_DEVICE_H__

#include "OgeBase/OgeInterfaces/IUnknown.h"
#include "OgeBase/OgeInterfaces/IInput.h"

#include <string>
#include <vector>

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

        enum                                  { IID =  3262838957 };

        enum InputType                        { Digital = 0, Analog = 1 , Position = 2 };

        typedef std::vector< IInput::RefPtr > IInputs;

        virtual void                          init() = 0; 

        virtual void                          config( const std::string& config ) = 0;

        virtual void                          start() = 0;

        virtual void                          update() = 0;   

        virtual IInput*                       getInput( InputType type, const unsigned int& index ) const = 0;        

        virtual IInputs&                      getInputs( InputType type ) = 0;

        virtual unsigned int                  getCount( InputType type ) const = 0;
      };
    } // namespace OgeInterfaces. 
  } // namespace OgeBase.
} // namespace Oge.

#endif // __OGE_INTERFACES_I_INPUT_DEVICE_H__
