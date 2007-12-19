
#include "Oge/OgeVrj/VrjDev/Gamepad.h"

// @Temp
#include "Oge/OgeVrj/VrjCore/VrjDigitalInput.h"
#include "Oge/OgeVrj/VrjCore/VrjAnalogInput.h"
#include "Oge/OgeVrj/VrjCore/VrjPositionInput.h"

#include <ostream>

namespace Oge
{
  namespace OgeVrj
  {
    namespace VrjDev
    {
      Gamepad::Gamepad( const unsigned int& digitalsCount, 
                        const unsigned int& analogsCount, 
                        const unsigned int& positionalsCount ) :
        _digitalInputs    ( digitalsCount ), 
        _analogInputs     ( analogsCount ), 
        _positionalInputs ( positionalsCount )
      {
        init();
      }


      Gamepad::~Gamepad()
      {
      }


      void Gamepad::init()
      {
        // Can we query hardware here? 
        // Also we test123need to have default config that program will look for. 
        config( "" );
      }


      void Gamepad::config( const std::string& config )
      {
        // Will tell how many digital and analog inputs are there.
        // Settings for each of the input
        // How do we do the binding? 
        // We need to know what kind of interface they are using? 
        // such as VRJ or SDL. Is it worth the effort? 
        for( size_t i = 0; i < _digitalInputs.size(); ++i )
        {
          std::ostringstream oStrStream1, oStrStream2; 
          oStrStream1 << i << std::endl;
          oStrStream2 << "Gamepad01Button" << i << "\0";

          _digitalInputs.push_back( new OgeVrj::VrjCore::VrjDigitalInput( oStrStream1.str(), oStrStream2.str().c_str() ) );
          _digitalInputs[ i ]->init();
        }

        // Analog inputs. 
        for( size_t i = 0; i < _analogInputs.size(); ++i )
        {
          std::ostringstream oStrStream1, oStrStream2; 
          oStrStream1 << i << std::endl;
          oStrStream2 << "Gamepad01Analog" << i << "\0";

          _analogInputs.push_back( new OgeVrj::VrjCore::VrjAnalogInput( oStrStream1.str(), oStrStream2.str().c_str() ) );
          _analogInputs[ i ]->init();
        }

        // Position inputs. 
        for( size_t i = 0; i < _digitalInputs.size(); ++i )
        {
          std::ostringstream oStrStream1, oStrStream2; 
          oStrStream1 << i << std::endl;
          oStrStream2 << "Gamepad01Position" << i << "\0";

          _positionalInputs.push_back( new OgeVrj::VrjCore::VrjPositionInput( oStrStream1.str(), oStrStream2.str().c_str() ) );
          _positionalInputs[ i ]->init();          
        }
      }


      void Gamepad::update()
      {
        InputsItr itr;
        for( itr  = _digitalInputs.begin(); itr != _digitalInputs.end(); ++itr )
        {
           ( *itr )->call( ( *itr )->getEvent() );          
        }

        for( itr  = _analogInputs.begin(); itr != _analogInputs.end(); ++itr )
        {
          ( *itr )->call( ( *itr )->getEvent() );
        }

        for( itr  = _positionalInputs.begin(); itr != _positionalInputs.end(); ++itr )
        {
          ( *itr )->call( ( *itr )->getEvent() );          
        }
      }


      OgeBase::OgeInterfaces::IInput* Gamepad::getInput( IInputDevice::InputType type, const unsigned int& index ) const
      {
        switch( type )
        {
          case IInputDevice::DIGITAL :
          {
            if( index < _digitalInputs.size() ) { return _digitalInputs.at( index ).get(); }
            else { return 0x00; }
          }
          case IInputDevice::ANALOG : 
          {
            if( index < _analogInputs.size() ) { return _analogInputs.at( index ).get(); }
            else { return 0x00; }
          }
          case IInputDevice::POSITIONAL : 
          {
            if( index < _positionalInputs.size() ){ return _positionalInputs.at( index ).get(); }
            else { return 0x00; }
          }
          default:
          {
            return 0x00;
          }
        };
      }
    

      unsigned int Gamepad::getCount( IInputDevice::InputType type ) const 
      {
        switch( type )
        {
          case DIGITAL: 
          {
            return _digitalInputs.size();
          }
          case ANALOG:
          {
            return _analogInputs.size();
          }
          case POSITIONAL:
          {
            return _positionalInputs.size();
          }
          default: 
          {
            // Error message here... 
            return 0;
          }
        };
      }


      OgeBase::OgeInterfaces::IUnknown* Gamepad::queryInterface( const unsigned long& iid )
      {
        return 0x00;
      }
    }
  }
}

