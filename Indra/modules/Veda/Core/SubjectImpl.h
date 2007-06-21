
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
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

#ifndef __DT_SUBJECT_IMPL_H__
#define __DT_SUBJECT_IMPL_H__

#include "tweek/tweekConfig.h"
#include "tweek/CORBA/SubjectImpl.h"

#include "vpr/IO/SerializableObject.h"
#include "vpr/IO/ObjectReader.h"
#include "vpr/IO/ObjectWriter.h"
#include "plugins/ApplicationDataManager/UserData.h"

#include "Tweek/dtsubject.h"

#include "Core/CommandFactory.h"
#include "Core/UserData.h"

#include "Tweek/TweekCommand.h"

#include "Core/Export.h"

namespace dt
{
  class VEDA_EXPORT SubjectImpl : public POA_dt::DtSubject, public tweek::SubjectImpl
  {
    public:
      SubjectImpl() : tweek::SubjectImpl()
      {}

      virtual ~SubjectImpl()
      {}

      void init()
      {}

      
      virtual void setCommand( const char* identifier, 
                   const char* entity, 
                   const char* state_attribute,
                   const char* modifier_string,
                   CORBA::Boolean modifier_boolean, 
                   CORBA::Long modifier_long );
      
      dt::DtSubject_ptr _this()
      {
        return POA_dt::DtSubject::_this();
      }
  };
}

#endif  // __DT_SUBJECT_IMPL_H__ 
