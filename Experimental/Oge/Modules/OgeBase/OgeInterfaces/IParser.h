
#ifndef __OGE_INTERFACES_I_PARSER_H__
#define __OGE_INTERFACES_I_PARSER_H__

#include "OgeBase/Export.h"
#include "OgeBase/OgeInterfaces/IUnknown.h"

#include <string>

namespace Oge
{
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      class IModel;

      class IParser : public IUnknown
      {
        public: 
          
          OGE_DELCARE_SMART_PTR( IParser );
          
          virtual void parse( const std::string& filename, IModel* model ) = 0;
      };
    }
  }
}

#endif // __OGE_INTERFACES_I_PARSER_H__
