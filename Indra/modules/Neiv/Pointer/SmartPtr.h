
#ifndef __NEIV_POINTER_SMARTPTR_H__
#define __NEIV_POINTER_SMARTPTR_H__

namespace Neiv
{
  namespace Pointer
  {    
	    template< typename T > 
      class SmartPtr 
	    {
		    public:

          /////////////////////////////////////////////////////////////////////
          //
          // Constructor. 
          //
          /////////////////////////////////////////////////////////////////////

			    SmartPtr() :
				    mPtr( 0 )
			    {
          }


          /////////////////////////////////////////////////////////////////////
          //
          // Constructor with pointer argument. 
          //
          /////////////////////////////////////////////////////////////////////

			    SmartPtr( T* ptr ) :
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


          /////////////////////////////////////////////////////////////////////
          //
          // Assignment operator ( overloaded ).
          // Note@: Making sure that we dont assign smart pointer to itself. 
          //
          /////////////////////////////////////////////////////////////////////

			    SmartPtr& operator = ( const SmartPtr& sp )
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

          SmartPtr& operator = ( SmartPtr* ptr )
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
          
          bool operator == ( const SmartPtr& sp ) const
          {
            return ( sp.mPtr == mPtr );
          }

          bool operator == ( const SmartPtr* ptr ) const
          {
            return ( ptr == mPtr );
          }

          friend bool operator == ( const SmartPtr* ptr, const SmartPtr& sp ) 
          {
            return ( ptr == sp.mPtr );
          }

          bool operator != ( const SmartPtr& sp ) const
          {
            return ( sp.mPtr == mPtr );
          }

          bool operator != ( const SmartPtr* ptr ) const
          {
            return ( ptr == mPtr );
          }

          friend bool operator != ( const SmartPtr* ptr, const SmartPtr& sp )
          {
            return ( ptr == sp.mPtr );
          }

          bool operator < ( const SmartPtr& sp ) const
          {
            return ( mPtr < sp.mPtr );
          }

          bool operator > ( const SmartPtr& sp ) const
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

          void swap( SmartPtr& sp )
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


#endif // __NEIV_POINTER_SMARTPTR_H__


