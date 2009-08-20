
#include "OgeBase/OgeInterfaces/IInputEventActionMap.h"

template< typename T1, typename T2 >
struct InputEventActionMap : public IInputEventActionMap< T1, T2 >
{
  struct InputEventAction
  {
    InputEventAction( const T1& input, const T2& eventType, IFunctor* ftor ) : 
      _input( input ), 
      _eventType( eventType ), 
      _ftor( ftor )
    {
    }

    T1        _input;
    T2        _eventType;
    IFunctor* _ftor;
  };

  // Add replace 
  // Add set
  // Add should add more functors to the same key and event type .. 

  virtual void addInputEventAction( const T1& input, const T2& eventType, IFunctor* ftor )
  {
    _inputEventActions.push_back( InputEventAction( input, eventType, ftor ) );
  }

  std::vector< InputEventAction > _inputEventActions;
};