#ifndef __MSG_CORE_SMART_PTR_H__
#define __MSG_CORE_SMART_PTR_H__

#include "Export.h"

#include <iostream>

namespace Mirage
{
  namespace MirageCore
  {
	  template< class T >
	  class SmartPtr 
	  {
		  public:
			  SmartPtr() :
				  _ptr( 0 )
			  {
        }


			  SmartPtr( T* ptr ) :
				  _ptr( ptr )
			  {
				  if( _ptr ) 
				  {
					  _ptr->ref();
				  }
			  }


			  SmartPtr( const SmartPtr& sp ) :
				  _ptr( sp._ptr )
			  {
				  if( _ptr )
				  {
					  _ptr->ref();
				  }
			  }	


		   ~SmartPtr()
			  {
				  if( _ptr )
				  {
					  _ptr->unref();
				  }
			  }


			  SmartPtr& operator = ( const SmartPtr& sp )
			  {
				  if( _ptr == sp._ptr )
					  return *this;
  				
				  T* tmpPtr = _ptr;
				  _ptr = sp._ptr;
				  _ptr->ref();

				  if( tmpPtr )
				  {
					  tmpPtr->unref();
				  }

				  return *this;				
			  }


			  SmartPtr& operator = ( T* ptr )
			  {
				  if( _ptr == ptr )
					  return *this;
  				
				  T* tmpPtr = _ptr;
				  _ptr = ptr;

				  if( _ptr )
				  {
					  _ptr->ref();
				  }

				  if( tmpPtr )
				  {
					  tmpPtr->unref();
				  }

				  return *this;
			  }


			  T* operator -> ()
			  {
				  return _ptr;
			  }


			  T* operator -> () const
			  {
				  return _ptr;
			  }


			  bool valid() const
			  {
				  return _ptr != 0;
			  }


			  T* get() const
			  {
				  return _ptr;
			  }


			  T* release()
			  {
				  T* tmpPtr = _ptr; 
				  if( _ptr )
				  {
					  _ptr->unrefDoNotDelete();
					  _ptr = 0;
					  return tmpPtr;
				  }
				  else
				  {
					  return 0;
				  }
			  }

		  private:

			  T* _ptr;
	  };
  }
}

#endif // __MSG_CORE_SMART_PTR_H__
