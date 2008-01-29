
#include "Oge/OgeVrj/VrjDev/Tracker.h"

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
      Tracker::Tracker( const unsigned int& digitalsCount, 
                        const unsigned int& analogsCount, 
                        const unsigned int& positionsCount ) :
        _start            ( false ),
        _digitalInputs    ( digitalsCount ), 
        _analogInputs     ( analogsCount ), 
        _positionInputs   ( positionsCount )
      {
        init();
      }


      Tracker::~Tracker()
      {
      }


      void Tracker::init()
      {
        // Can we query hardware here? 
        // Also we test123need to have default config that program will look for. 
        config( "" );
      }


      void Tracker::config( const std::string& config )
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
          oStrStream2 << "Tracker01Button0" << i+1 << "\0";

          _digitalInputs[ i ] = new OgeVrj::VrjCore::VrjDigitalInput( oStrStream1.str(), oStrStream2.str().c_str() ) ;
          _digitalInputs[ i ]->init();
        }

        // Analog inputs. 
        for( size_t i = 0; i < _analogInputs.size(); ++i )
        {
          std::ostringstream oStrStream1, oStrStream2; 
          oStrStream1 << i << std::endl;
          oStrStream2 << "Tracker01Analog0" << i + 1 << "\0";

          _analogInputs[ i ] = new OgeVrj::VrjCore::VrjAnalogInput( oStrStream1.str(), oStrStream2.str().c_str() );
          _analogInputs[ i ]->init();
        }

        // Position inputs. 
        for( size_t i = 0; i < _positionInputs.size(); ++i )
        {
          std::ostringstream oStrStream1, oStrStream2; 
          oStrStream1 << i << std::endl;
	  if( i == 0 )
            oStrStream2 << "Tracker01Head01Proxy" << "\0";
	   else
            oStrStream2 << "Tracker01Wand01Proxy" << "\0";

          _positionInputs[ i ] = new OgeVrj::VrjCore::VrjPositionInput( oStrStream1.str(), oStrStream2.str().c_str() );
          _positionInputs[ i ]->init();          
        }
      }


      void Tracker::start()
      {
        _start = true;
      }


      void Tracker::update()
      {
        InputsItr itr;
        for( itr  = _digitalInputs.begin(); itr != _digitalInputs.end(); ++itr )
        {
           ( *itr )->call( ( *itr )->getEvent() );          
        }

        if( _start )
        {
          for( itr  = _analogInputs.begin(); itr != _analogInputs.end(); ++itr )
          {
            ( *itr )->call( ( *itr )->getEvent() );
          }

          for( itr  = _positionInputs.begin(); itr != _positionInputs.end(); ++itr )
          {
            ( *itr )->call( ( *itr )->getEvent() );          
          }
        }
      }


      OgeBase::OgeInterfaces::IInput* Tracker::getInput( IInputDevice::InputType type, const unsigned int& index ) const
      {
        switch( type )
        {
          case IInputDevice::Digital :
          {
            if( index < _digitalInputs.size() ) { return _digitalInputs.at( index ).get(); }
            else { return 0x00; }
          }
          case IInputDevice::Analog : 
          {
            if( index < _analogInputs.size() ) { return _analogInputs.at( index ).get(); }
            else { return 0x00; }
          }
          case IInputDevice::Position : 
          {
            if( index < _positionInputs.size() ){ return _positionInputs.at( index ).get(); }
            else { return 0x00; }
          }
          default:
          {
            return 0x00;
          }
        };
      }


      Tracker::IInputs& Tracker::getInputs( IInputDevice::InputType type )
      {
        switch( type )
        {
          case IInputDevice::Digital : 
          {
            return _digitalInputs;
          }
          case IInputDevice::Analog:
          {
            return _analogInputs;
          }
          case IInputDevice::Position: 
          {
            return _positionInputs;
          }          
          default :
          {
            throw "Error 1127219602t InputType not recognized: ";
          }
        };
      }
    

      unsigned int Tracker::getCount( IInputDevice::InputType type ) const 
      {
        switch( type )
        {
          case Digital: 
          {
            return _digitalInputs.size();
          }
          case Analog:
          {
            return _analogInputs.size();
          }
          case Position:
          {
            return _positionInputs.size();
          }
          default: 
          {
            // Error message here... 
            return 0;
          }
        };
      }


      OgeBase::OgeInterfaces::IUnknown* Tracker::queryInterface( const unsigned long& iid )
      {
        return 0x00;
      }
    }
  }
}

