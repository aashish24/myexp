
#ifndef __OGE_CORE_BASE_VIEWER_H__
#define __OGE_CORE_BASE_VIEWER_H__

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IBaseViewer.h"
#include "Oge/OgeBase/OgeInterfaces/IInputDevice.h"
#include "Oge/OgeBase/OgeInterfaces/IInterfaceContext.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"


#include <vector>
#include <map>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    { 
      class OGE_EXPORT BaseViewer :                 
        public Oge::OgeBase::OgeInterfaces::IBaseViewer,
        public Oge::OgeBase::OgeCore::Referenced        
      {

        public : 

          OGE_DELCARE_SMART_PTR( BaseViewer );     

          IMPLEMENT_IUNKNOWN_MEMBERS( BaseViewer, Oge::OgeBase::OgeCore::Referenced );

          typedef OgeBase::OgeInterfaces::IUnknown                      IUnknown;          
          typedef OgeBase::OgeInterfaces::IInputDevice                  IInputDevice;
          typedef OgeBase::OgeInterfaces::IInterfaceContext             IInterfaceContext;
          
          typedef std::map< const std::string, IInputDevice::RefPtr >   InputDevices;
          typedef std::vector< IInterfaceContext::RefPtr >              OgeContexts;

          BaseViewer( int argc = 0, char** argv = 0 );        

          virtual void                                                  init();

          virtual void                                                  update();
          
          virtual IUnknown*                                             queryInterface( const unsigned long& iid );

          virtual void                                                  addInputDevice( const std::string& deviceName, IInputDevice* inputDevice );

          virtual IInputDevice*                                         getInputDevice( const std::string& deviceName ) const;

          virtual void                                                  addInterfaceContext( IInterfaceContext* context );

          virtual IInterfaceContext*                                    getInterfaceContext( const unsigned int& index ) const;        

      
      protected: 
      
          virtual                                                       ~BaseViewer();    


        protected: 
          
          InputDevices                                                  _inputDevices;
          OgeContexts                                                   _interfaceContexts;
      };
    }
  } 
} 

#endif // __OGE_CORE_BASE_VIEWER_H__
