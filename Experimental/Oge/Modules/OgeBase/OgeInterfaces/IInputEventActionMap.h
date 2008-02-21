

#ifndef __OGE_INTERFACES_I_ACTION_CALLBACK_H__
#define __OGE_INTERFACES_I_ACTION_CALLBACK_H__

namespace Oge 
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      struct IFunctor; 
  
      template< typename T1, typename T2 >
      struct IEventActionGlue : public IUnknown
      {
        virtual void add( const IInput& input, const IEvent& event, IFunctor* ftor ) = 0; 
      };
    } // namespace OgeInterfaces. 
  } // namespace OgeBase.
} // namespace Og.e

#endif // __OGE_INTERFACES_I_ACTION_CALLBACK_H__


/* 
  if( js->input( 0 )->getData() != NULL )
  {
    performAction( js->input( 0 ));
  }

  // somwhere call would be like this. 
  // Data and event can be queried as js->getData(), js->getEvent(). 

  call( IInput* input, DATA data, EVENT event )
  {
    // Here find the functor for which 
    // _input = input 
    // _event = event
    // and pass this data. 
  }
*/
