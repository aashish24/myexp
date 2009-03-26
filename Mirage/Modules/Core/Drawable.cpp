
#include "Core/Drawable.h"

namespace Mirage
{
  namespace Core
  {
    Drawable::Drawable() :
      _useDisplayList( true ), 
      _glObjectList  ( 0x00 )
    {
    }


    Drawable::Drawable( const Mirage::Core::Drawable &drawable )      
    {
    }


    void Drawable::drawImplementation() 
		{					
		}
  }
}



