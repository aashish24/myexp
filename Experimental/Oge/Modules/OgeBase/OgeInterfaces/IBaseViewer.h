
#ifndef __OGE_INTERFACES_I_BASE_VIEWER_H__
#define __OGE_INTERFACES_I_BASE_VIEWER_H__

#include "Oge/OgeBase/OgeInterfaces/IUnknown.h"

#include <string>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    { 
      struct IInputDevice;      
      struct IInterfaceContext;

      /////////////////////////////////////////////////////////////////////////
      //
      // We should have some interface for event handling here. 
      // Also how the user would have to set whether or not this viewer is embedded 
      // in an external window in the constrcutor. We could provide some interface 
      // later but for now lets keep it simple. 
      //
      ///////////////////////////////////////////////////////////////////////

      struct IBaseViewer : public IUnknown
      {
        OGE_DELCARE_SMART_PTR( IBaseViewer );

        enum                        { IID = 3891231455 };

        virtual void                init() = 0;

        virtual void                update() = 0;

        virtual void                addInputDevice( const std::string& deviceName, IInputDevice* inputDevice ) = 0;

        virtual IInputDevice*       getInputDevice( const std::string& deviceName ) const = 0;

        virtual void                addInterfaceContext( IInterfaceContext* context ) = 0;
        
        virtual IInterfaceContext*  getInterfaceContext( const unsigned int& index ) const = 0;
      };
    } 
  } 
} 

#endif // __OGE_INTERFACES_I_BASE_VIEWER_H__
