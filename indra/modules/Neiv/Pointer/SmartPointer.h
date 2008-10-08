
#ifndef __NEIV_POINTER_SMARTPOINTER_H__
#define __NEIV_POINTER_SMARTPOINTER_H__

// This should be the first include. 
#include "Neiv/NeivConfig.h"

namespace Neiv
{
  namespace Pointer
  {    
	    template< typename T > 
      class SmartPointer 
	    {
		    public:

          /////////////////////////////////////////////////////////////////////
          //
          // Constructor. 
          //
          /////////////////////////////////////////////////////////////////////

			    SmartPointer() :
				    mPtr( 0 )
			    {
          }


          /////////////////////////////////////////////////////////////////////
          //
          // Constructor with pointer argument. 
          //
          /////////////////////////////////////////////////////////////////////

			    SmartPointer( T* ptr ) :
				    mPtr( ptr )
			    {
				    if( mPtr ) 
				    {
					    mPtr->ref();
				    }
			    }


          /////////////////////////////////////////////////////////////////////
          //
          // Copy constructor. 
          //
          /////////////////////////////////////////////////////////////////////

			    SmartPointer( const SmartPointer& sp ) :
				    mPtr( sp.mPtr )
			    {
				    if( mPtr )
				    {
					    mPtr->ref();
				    }
			    }	

		       ~SmartPointer()
			    {
				    if( mPtr )
				    {
					    mPtr->unref();
				    }
			    }


          /////////////////////////////////////////////////////////////////////
          //
          // Assignment operator ( overloaded ).
          // Note@: Making sure that we dont assign smart pointer to itself. 
          //
          /////////////////////////////////////////////////////////////////////

			    SmartPointer& operator = ( const SmartPointer& sp )
			    {
				    if( mPtr == sp.mPtr )
					    return *this;
    				
				    T* tmpPtr = mPtr;
				    mPtr = sp.mPtr;
				    
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

          SmartPointer& operator = ( SmartPointer* ptr )
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

          
          /////////////////////////////////////////////////////////////////////
          //
          // Comparison operators.
          // 
          /////////////////////////////////////////////////////////////////////			   
          
          bool operator == ( const SmartPointer& sp ) const
          {
            return ( sp.mPtr == mPtr );
          }

          bool operator == ( const SmartPointer* ptr ) const
          {
            return ( ptr == mPtr );
          }

          friend bool operator == ( const SmartPointer* ptr, const SmartPointer& sp ) 
          {
            return ( ptr == sp.mPtr );
          }

          bool operator != ( const SmartPointer& sp ) const
          {
            return ( sp.mPtr == mPtr );
          }

          bool operator != ( const SmartPointer* ptr ) const
          {
            return ( ptr == mPtr );
          }

          friend bool operator != ( const SmartPointer* ptr, const SmartPointer& sp )
          {
            return ( ptr == sp.mPtr );
          }

          bool operator < ( const SmartPointer& sp ) const
          {
            return ( mPtr < sp.mPtr );
          }

          bool operator > ( const SmartPointer& sp ) const
          {
            return ( mPtr > sp.mPtr );
          }


          /////////////////////////////////////////////////////////////////////
          //
          // Element selection through pointer operator ( overloaded ).
          // 
          /////////////////////////////////////////////////////////////////////			   

			    T* operator -> () const
			    {
				    return mPtr;
			    }


          /////////////////////////////////////////////////////////////////////
          //
          // Check for null pointers. 
          //
          /////////////////////////////////////////////////////////////////////

			    bool valid() const
			    {
				    return mPtr != 0;
			    }


          /////////////////////////////////////////////////////////////////////
          //
          // Return raw pointer. 
          //
          /////////////////////////////////////////////////////////////////////

			    T* get() const
			    {
				    return mPtr;
			    }


          /////////////////////////////////////////////////////////////////////
          //
          // Return raw pointer. 
          // Note@ Making sure that we dont not delete it even though the count 
          // goes to zero. 
          //
          /////////////////////////////////////////////////////////////////////

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


          /////////////////////////////////////////////////////////////////////
          //
          // Swap the pointers. 
          //
          /////////////////////////////////////////////////////////////////////

          void swap( SmartPointer& sp )
          {
            T* tmp = mPtr;
            mPtr = sp.mPtr;
            sp.mPtr = tmp;
          }

		    private:

			    T* mPtr;
	    };
    }
  }


#endif // __NEIV_POINTER_SMARTPOINTER_H__


