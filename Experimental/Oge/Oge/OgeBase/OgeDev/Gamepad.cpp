
#include "Oge/OgeBase/OgeDev/Gamepad.h"

// @Temp
#include "Oge/OgeVrj/VrjController/VrjDigitalInput.h"

#include <ostream>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeDev
    {
      Gamepad::Gamepad() 
      {
        init();
      }


      Gamepad::~Gamepad()
      {
      }


      void Gamepad::init()
      {
        // Can we query hardware here? 
        // Also we need to have default config that program will look for. 
        config( "" );
      }


      void Gamepad::config( const std::string& config )
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

          _inputs.push_back( new OgeVrj::VrjController::VrjDigitalInput( oStrStream1.str(), "VJButton0" ) );
          _inputs[ i ]->init();
          //_inputs[ i ]->addActionCallback( Oge::OgeBase::OgeInterfaces::IEvent::KeyPress, testFtor, true );
        }
      }


      void Gamepad::update()
      {
        for( size_t i = 0; i < 1; ++i )
        {
          _inputs[ i ]->call( _inputs[ i ]->getEvent() );
        }
      }


      OgeInterfaces::IInput* Gamepad::getInput( const unsigned int& index )
      {
        if( index >= _inputs.size() )
        {
          return 0x00;
        }

        return _inputs[ index ];
      }
    

      OgeInterfaces::IUnknown* Gamepad::queryInterface( const unsigned long& iid )
      {
        return 0x00;
      }
    }
  }
}

