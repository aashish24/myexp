#ifndef __SMART_PTR_H__
#define __SMART_PTR_H__

#include <oge/Export.h>

#include <iostream>

namespace oge
{
	template< class T >
	class OGE_EXPORT SmartPtr 
	{
		public:
			SmartPtr() :
				mPtr( 0 )
			{}

			SmartPtr( T* ptr ) :
				mPtr( ptr )
			{
				if( mPtr ) 
				{
					mPtr->ref();
				}
			}

			SmartPtr( const SmartPtr& sp ) :
				mPtr( sp.mPtr )
			{
				if( mPtr )
				{
					mPtr->ref();
				}
			}	

		   ~SmartPtr()
			{
				if( mPtr )
				{
					mPtr->unref();
				}
			}

			SmartPtr& operator = ( const SmartPtr& sp )
			{
				if( mPtr == sp.mPtr )
					return *this;
				
				T* tmpPtr = mPtr;
				mPtr = sp.mPtr;
				mPtr->ref();

				if( tmpPtr )
				{
					tmpPtr->unref();
				}

				return *this;				
			}

			SmartPtr& operator = ( T* ptr )
			{
				if( mPtr == ptr )
					return *this;
				
				T* tmpPtr = mPtr;
				mPtr = ptr;

				if( mPtr )
				{
					mPtr->ref();
				}

				if( tmpPtr )
				{
					tmpPtr->unref();
				}

				return *this;
			}

			T* operator -> ()
			{
				return mPtr;
			}

			T* operator -> () const
			{
				return mPtr;
			}

			bool valid() const
			{
				return mPtr != 0;
			}

			T* get() const
			{
				return mPtr;
			}

			T* release()
			{
				T* tmpPtr = mPtr; 
				if( mPtr )
				{
					mPtr->unrefDoNotDelete();
					mPtr = 0;
					return tmpPtr;
				}
				else
				{
					return 0;
				}
			}

		private:
			T* mPtr;
	};
}

#endif // __SMART_PTR_H__