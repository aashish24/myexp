
#include "MsgCore/StateAttribute.h"

namespace Msg
{
  namespace MsgCore
  {
    StateAttribute::StateAttribute( const bool& flag, const int& maskVal ) :
      Object  (),
      _dirty  ( flag ), 
      _mask   ( maskVal ) 
    {
    }


    StateAttribute::~StateAttribute()
    {
    }


    bool StateAttribute::dirty() const 
    {
      return _dirty;
    }


    void StateAttribute::dirty( const bool& flag )
    {
      _dirty = flag;
    }


    const int& StateAttribute::mask() const 
    {
      return _mask;
    }


    void StateAttribute::mask( const int& maskVal )
    {
      _mask = maskVal;
    }
  }
}
