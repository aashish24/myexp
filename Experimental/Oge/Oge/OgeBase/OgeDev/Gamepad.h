
#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeCore/MemberFunctor.h"

#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"

#include "Oge/OgeVrj/VrjController/VrjDigitalInput.h"


#include <ostream>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
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

      class Gamepad : public  OgeInterfaces::IInputDevice, OgeCore::Referenced
      {
        public:
          
          typedef Oge::OgeBase::OgeInterfaces::IInput         IInput;
          typedef Oge::OgeVrj::VrjController::VrjDigitalInput VrjDigitalInput;

          Gamepad() 
          {
            init();
          }


          virtual void init()
          {
            // Can we query hardware here? 
            config( "" );
          }

          virtual void config( const std::string& config )
          {
            // Will tell how many digital and analog inputs are there.
            // Settings for each of the input
            // How do we do the binding? 
            // We need to know what kind of interface they are using? 
            // such as VRJ or SDL. Is it worth the effort? 

            /*Test test;
            Oge::OgeBase::OgeCore::MemberFunctor< Test >* testFtor = new Oge::OgeBase::OgeCore::MemberFunctor< Test >( &test, &Test::print );*/

            for( size_t i = 0; i < 1; ++i )
            {
              std::ostringstream oStrStream1, oStrStream2; 
              oStrStream1 << i << std::endl;
              oStrStream2 << "Gamepad01Button" << "0" << i << std::endl;

              _inputs.push_back( new VrjDigitalInput( oStrStream1.str(), "VJButton0" ) );
              _inputs[ i ]->init();
              //_inputs[ i ]->addActionCallback( Oge::OgeBase::OgeInterfaces::IEvent::KeyPress, testFtor, true );
            }
          }


          virtual void update()
          {
            for( size_t i = 0; i < 1; ++i )
            {
              _inputs[ i ]->call( _inputs[ i ]->getEvent() );
            }
          }


          virtual IInput* getInput( const unsigned int& index )
          {
            if( index >= _inputs.size() )
            {
              return 0x00;
            }

            return _inputs[ index ];
          }
        

          virtual IUnknown* queryInterface( const unsigned long& iid )
          {
            return 0x00;
          }

        
        protected: 
          
          virtual ~Gamepad()
          {
          }

        protected: 

          std::vector< IInput* > _inputs;
      };
    }
  }
}

#endif // __GAMEPAD_H__
