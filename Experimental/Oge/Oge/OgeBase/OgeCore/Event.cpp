
#include "Oge/OgeBase/OgeCore/Event.h" 


namespace Oge
{
  namespace OgeBase
  {
    namespace OgeCore
    {
      Event::Event( Type type ) : _type( type )
      {
      }
      
      
      Event::~Event()
      {
      }


      Type Event::type() const
      {
        return _type;
      }
    }
  }
}
