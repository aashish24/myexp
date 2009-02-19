
#include "MirageCore/Drawable.h"

namespace Mirage
{
  namespace MirageCore
  {
    Drawable::Drawable() :
      _useDisplayList( true ), 
      _glObjectList  ( 0x00 )
    {
    }


    Drawable::Drawable( const Mirage::MirageCore::Drawable &drawable )      
    {
    }


    void Drawable::drawImplementation() 
		{					
		}
  }
}



