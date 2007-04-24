
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Aashish Chaudhary
//
///////////////////////////////////////////////////////////////////////////////

// This file is generated by omniidl (C++ backend)- omniORB_4_0. Do not edit.
#ifndef __dtsubject_hh__
#define __dtsubject_hh__

#ifndef USE_omniORB_logStream
#define USE_omniORB_logStream
#endif

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_dtsubject
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_dtsubject
#endif



#ifndef __Observer_hh_EXTERNAL_GUARD__
#define __Observer_hh_EXTERNAL_GUARD__
#include <Observer.h>
#endif
#ifndef __Subject_hh_EXTERNAL_GUARD__
#define __Subject_hh_EXTERNAL_GUARD__
#include <Subject.h>
#endif



#ifdef USE_stub_in_nt_dll
#ifndef USE_core_stub_in_nt_dll
#define USE_core_stub_in_nt_dll
#endif
#ifndef USE_dyn_stub_in_nt_dll
#define USE_dyn_stub_in_nt_dll
#endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif





_CORBA_MODULE dt

_CORBA_MODULE_BEG

  typedef char* string_var;
  typedef CORBA::String_var string_var_var;
  typedef CORBA::String_out string_var_out;

#ifndef __dt_mDtSubject__
#define __dt_mDtSubject__

  class DtSubject;
  class _objref_DtSubject;
  class _impl_DtSubject;
  
  typedef _objref_DtSubject* DtSubject_ptr;
  typedef DtSubject_ptr DtSubjectRef;

  class DtSubject_Helper {
  public:
    typedef DtSubject_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_DtSubject, DtSubject_Helper> DtSubject_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_DtSubject,DtSubject_Helper > DtSubject_out;

#endif

  class DtSubject {
  public:
    // Declarations for this interface type.
    typedef DtSubject_ptr _ptr_type;
    typedef DtSubject_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(CORBA::Object_ptr);
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    
  };

  class _objref_DtSubject :
    public virtual tweek::_objref_Subject
  {
  public:
    void setCommand(const char* identifier, const char* entity, const char* state_attribute, const char* modifier_string, CORBA::Boolean modifier_boolean, CORBA::Long modifier_long);

    inline _objref_DtSubject()  { _PR_setobj(0); }  // nil
    _objref_DtSubject(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_DtSubject();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_DtSubject(const _objref_DtSubject&);
    _objref_DtSubject& operator = (const _objref_DtSubject&);
    // not implemented

    friend class DtSubject;
  };

  class _pof_DtSubject : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_DtSubject() : _OMNI_NS(proxyObjectFactory)(DtSubject::_PD_repoId) {}
    virtual ~_pof_DtSubject();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_DtSubject :
    public virtual tweek::_impl_Subject
  {
  public:
    virtual ~_impl_DtSubject();

    virtual void setCommand(const char* identifier, const char* entity, const char* state_attribute, const char* modifier_string, CORBA::Boolean modifier_boolean, CORBA::Long modifier_long) = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
  };


_CORBA_MODULE_END



_CORBA_MODULE POA_dt
_CORBA_MODULE_BEG

  class DtSubject :
    public virtual dt::_impl_DtSubject,
    public virtual POA_tweek::Subject
  {
  public:
    virtual ~DtSubject();

    inline ::dt::DtSubject_ptr _this() {
      return (::dt::DtSubject_ptr) _do_this(::dt::DtSubject::_PD_repoId);
    }
  };

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr



inline void
dt::DtSubject::_marshalObjRef(::dt::DtSubject_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_dtsubject
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_dtsubject
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_dtsubject
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_dtsubject
#endif

#endif  // __dtsubject_hh__

