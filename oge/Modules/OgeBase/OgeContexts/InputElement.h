
#include <string>

namespace Oge
{
  namespace OgeBase 
  {
    namespace OgeController
    {   
      enum Type   { ANALOG = 1, DIGITAL = 1, POSITIONAL = 2 };      
      enum State  { DOWN = 1, UP = 2, TILT_BACK = 3, TILT_FWD = 4, TILT_LEFT = 5, TILT_RIGHT = 6  };

      struct InputElement
      {
        std::string   _id;   
        std::string   _proxy;
        Type          _type; 
      };
    }
  }
}