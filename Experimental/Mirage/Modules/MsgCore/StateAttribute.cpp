
#include "MsgCore/StateAttribute.h"

namespace Msg
{
  namespace MsgCore
  {
    StateAttribute::StateAttribute( const bool& flag ) :
      Object(),
      _dirty( flag )
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
  }
}
