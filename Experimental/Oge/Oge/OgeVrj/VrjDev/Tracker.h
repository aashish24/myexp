
#ifndef __VRJ_DEV_TRACKER_H__
#define __VRJ_DEV_TRACKER_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeCore/MemberFunctor.h"

#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"

#include "Oge/OgeVrj/VrjCore/VrjDigitalInput.h"


#include <ostream>

namespace Oge
{
  namespace OgeVrj
  {
    
    namespace OgeInterfaces
    {
      struct IUnknown; 
      struct IInput;        
    }

    namespace VrjDev
    { 
      class OGE_EXPORT Tracker : 
        public Oge::OgeBase::OgeInterfaces::IInputDevice, 
        public Oge::OgeBase::OgeCore::Referenced
      {
        public:
                                                                
          OGE_DELCARE_SMART_PTR( Tracker ); 

          IMPLEMENT_IUNKNOWN_MEMBERS( Tracker, Oge::OgeBase::OgeCore::Referenced );

          typedef OgeBase::OgeInterfaces::IUnknown                  IUnknown;
          typedef OgeBase::OgeInterfaces::IInput                    IInput;
          typedef std::vector< IInput::RefPtr >                     IInputs;
          typedef IInputs::iterator                                 InputsItr;

          Tracker( const unsigned int& digitalsCount  = 12, 
                   const unsigned int& analogsCount   = 6, 
                   const unsigned int& positionsCount = 0  );

          virtual void                                              init();

          virtual void                                              config( const std::string& config );

          virtual void                                              update();

          virtual OgeBase::OgeInterfaces::IInput*                   getInput( IInputDevice::InputType type, const unsigned int& index ) const;

          virtual IInputs&                                          getInputs( IInputDevice::InputType type );

          virtual unsigned int                                      getCount( IInputDevice::InputType type ) const;

          virtual IUnknown*                                         queryInterface( const unsigned long& iid );

          virtual void                                              start();

        
        protected: 
          
          virtual ~Tracker();


        protected: 

          bool                                                      _start;

          IInputs                                                   _digitalInputs;
          IInputs                                                   _analogInputs;
          IInputs                                                   _positionInputs;
      };
    }
  }
}

#endif // __VRJ_DEV_TRACKER_H__
