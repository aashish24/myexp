
#ifndef __OGE_DEV_GAMEPAD_H__
#define __OGE_DEV_GAMEPAD_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeCore/MemberFunctor.h"

#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"

#include "Oge/OgeVrj/VrjCore/VrjDigitalInput.h"


#include <ostream>

namespace Oge
{
  namespace OgeBase
  {
    
    namespace OgeInterfaces
    {
      struct IUnknown; 
      struct IInput;        
    }

    namespace OgeDev
    {
      class Test
      {
        public: 
          void print()
          {
            std::cout <<  "Print: " << std::endl;
          }
      };

      class OGE_EXPORT Gamepad : public  OgeInterfaces::IInputDevice
      {
        public:
                                                                
                                                              OGE_DELCARE_SMART_PTR( Gamepad ); 

                                                              Gamepad();


          virtual void                                        init();

          virtual void                                        config( const std::string& config );

          virtual void                                        update();

          virtual OgeInterfaces::IInput*                      getInput( const unsigned int& index );

          virtual OgeInterfaces::IUnknown*                    queryInterface( const unsigned long& iid );

        
        protected: 
          
          virtual                                             ~Gamepad();

        protected: 

          std::vector< OgeInterfaces::IInput* >                _inputs;
      };
    }
  }
}

#endif // __OGE_DEV_GAMEPAD_H__
