
#include "MsgCore/Drawable.h"

namespace Msg
{
  namespace MsgCore
  {
    Drawable::Drawable() :
      _useDisplayList( false ), 
      _glObjectList  ( 0x00 )
    {
    }


    Drawable::Drawable( const Msg::MsgCore::Drawable &drawable )      
    {
    }


    void Drawable::drawImplementation() 
		{					
		}
  }
}



