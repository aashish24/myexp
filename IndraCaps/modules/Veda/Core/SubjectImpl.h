
///////////////////////////////////////////////////////////////////////////////
//
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// This class VEDA_EXPORT provides tweek subject implementation. 
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __VEDA_SUBJECTIMPL_H__
#define __VEDA_SUBJECTIMPL_H__

// This should be the first include. 
#include "Veda/VedaConfig.h"

#include "tweek/tweekConfig.h"
#include "tweek/CORBA/SubjectImpl.h"

#include "vpr/IO/SerializableObject.h"
#include "vpr/IO/ObjectReader.h"
#include "vpr/IO/ObjectWriter.h"
#include "plugins/ApplicationDataManager/UserData.h"

#include "Veda/Tweek/TweekSubject.h"

#include "Veda/Core/CommandFactory.h"
#include "Veda/Core/UserData.h"

#include "Veda/Tweek/TweekCommand.h"

#include "Veda/Export.h"

namespace Veda
{
  class VEDA_EXPORT SubjectImpl : public POA_Veda::ITweek::TweekSubject, public tweek::SubjectImpl
  {
    public:
      SubjectImpl() : tweek::SubjectImpl()
      {}

      virtual ~SubjectImpl()
      {}

      void init()
      {}

      
      virtual void setCommand( const char* key, const char* value );
      
      Veda::ITweek::TweekSubject_ptr _this()
      {
        return POA_Veda::ITweek::TweekSubject::_this();
      }
  };
}

#endif  // __VEDA_SUBJECTIMPL_H__ 
