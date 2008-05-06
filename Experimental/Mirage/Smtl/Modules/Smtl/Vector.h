/******************************************************************************
 *
 * Class defines vectors and operations on vectors. 
 *
 ******************************************************************************
 */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <vector>
#include <math.h>
#include <assert.h>

namespace Smtl
{
	template< class DATA_TYPE, unsigned int SIZE >
	class Vector
	{
		public:
			
      Vector()
			{
				for( unsigned int i=0; i < SIZE; ++i )
				{
					this->mData[i] = ( DATA_TYPE )0 ;
				}
			}


			Vector( DATA_TYPE val0, DATA_TYPE val1 )
			{
				Vector();
				set( val0, val1 );
			}


			Vector( DATA_TYPE val0, DATA_TYPE val1, DATA_TYPE val2 )
			{
				Vector();
				set( val0, val1, val2 );
			}


			Vector( DATA_TYPE val0, DATA_TYPE val1, DATA_TYPE val2, DATA_TYPE val3 )
			{
				Vector();
				set( val0, val1, val2, val3 );
			}


			~Vector()
			{
      }


			DATA_TYPE& operator[]( unsigned int column )
			{
				assert( column < SIZE );
				return mData[column]; 
			}


			const DATA_TYPE& operator[]( unsigned int column ) const
			{
				assert( column < SIZE );
				return mData[column]; 
			}
			

			Vector< DATA_TYPE, SIZE >& operator=( const Vector< DATA_TYPE,SIZE >& rhs )
			{
				for( unsigned i = 0; i < SIZE; ++i )
				{
					mData[i] = rhs[i];
				}

				return *this;
			}


			bool operator==( const Vector< DATA_TYPE,SIZE >& rhs )
			{
				bool retVal = true;

				for( unsigned i = 0; i < SIZE; ++i )
				{
					if( mData[i] != rhs[i] )
					{
						retVal = false;
					}
				}

				return retVal;				
			}


			Vector< DATA_TYPE, SIZE >& operator+=( const Vector< DATA_TYPE,SIZE >& rhs )
			{
				for( unsigned i = 0; i < SIZE; ++i )
				{
					mData[i] = mData[i] + rhs[i];
				}

				return *this;
			}


			Vector< DATA_TYPE, SIZE >& operator-=( const Vector< DATA_TYPE,SIZE >& rhs )
			{
				for( unsigned i = 0; i < SIZE; ++i )
				{
					mData[i] = mData[i] - rhs[i];
				}

				return *this;
			}


			Vector< DATA_TYPE, SIZE >& operator*=( const Vector< DATA_TYPE,SIZE >& rhs )
			{
				for( unsigned i = 0; i < SIZE; ++i )
				{
					mData[i] = mData[i] * rhs[i];
				}

				return *this;
			}


			Vector< DATA_TYPE, SIZE >& operator/=( const Vector< DATA_TYPE,SIZE >& rhs )
			{
				for( unsigned i = 0; i < SIZE; ++i )
				{
					mData[i] = mData[i] / rhs[i];
				}

				return *this;
			}


			Vector< DATA_TYPE, SIZE > operator*( DATA_TYPE val )
			{
				Vector< DATA_TYPE, SIZE > vec;
				for( unsigned int i = 0; i < SIZE; ++i )
				{
					vec[i] = mData[i] * val;
				}

				return vec;
			}


			Vector< DATA_TYPE, SIZE > operator+( const Vector< DATA_TYPE,SIZE >& rhs )
			{
				Vector< DATA_TYPE, SIZE > vec;
				for( unsigned int i=0; i<SIZE; ++i )
				{
					vec[i] = mData[i] + rhs[i];
				}

				return vec;
			}


			Vector< DATA_TYPE, SIZE > operator-( const Vector< DATA_TYPE,SIZE >& rhs )
			{
				Vector< DATA_TYPE, SIZE > vec;
				for( unsigned int i=0; i<SIZE; ++i )
				{
					vec[i] = mData[i] - rhs[i];
				}

				return vec;
			}


			Vector< DATA_TYPE, SIZE > operator/( const Vector< DATA_TYPE, SIZE >& rhs )
			{
				Vector< DATA_TYPE, SIZE > vec;
				for( unsigned int i=0; i<SIZE; ++i )
				{
					vec[i] = mData[i] / rhs[i];
				}

				return vec;
			}


			Vector< DATA_TYPE, SIZE > operator-()
			{
				Vector< DATA_TYPE, SIZE > vec;
				for( unsigned int i=0; i<SIZE; ++i )
				{
					vec[i] = -mData[i];
				}

				return vec;
			}			


			Vector< DATA_TYPE, SIZE >* operator&( const Vector< DATA_TYPE, SIZE >& rhs )
			{
				return &rhs[0];
			}


			void set( DATA_TYPE val0, DATA_TYPE val1 )
			{
				mData[0] = val0;
				mData[1] = val1;
			}


			void set( DATA_TYPE val0, DATA_TYPE val1, DATA_TYPE val2 )
			{
				mData[0] = val0;
				mData[1] = val1;
				mData[2] = val2;
			}


			void set( DATA_TYPE val0, DATA_TYPE val1, DATA_TYPE val2, DATA_TYPE val3 )
			{
				mData[0] = val0;
				mData[1] = val1;
				mData[2] = val2;
				mData[3] = val3;
			}

			DATA_TYPE length()
			{
				DATA_TYPE mVal = (DATA_TYPE)0;

				for( unsigned int i=0; i<SIZE; ++i )
				{
					mVal = this->mData[i] * this->mData[i] + mVal;
				}

				return sqrt( mVal );
			}


			Vector< DATA_TYPE, SIZE >& normalize()
			{
        DATA_TYPE val = length();

				for( size_t i=0; i < SIZE; ++i )
				{          
          if( val != 0.0 )
          {
            mData[i] = mData[i] / val;
          }
          else
          {
            throw "ERROR 3614273646: Division by zero error. "; 
          }
				}

        return *this;
			}


			Vector< DATA_TYPE, SIZE > cross( Vector< DATA_TYPE, SIZE > vec2 )
			{
				Vector< DATA_TYPE, SIZE > resultVec;
				
				assert( SIZE == 3 );
				resultVec[0] = ( mData[1] * vec2[2] ) - ( mData[2] * vec2[1] );
				resultVec[1] = ( mData[2] * vec2[0] ) - ( mData[0] * vec2[2] );
				resultVec[2] = ( mData[0] * vec2[1] ) - ( mData[1] * vec2[0] );

				return resultVec;
			}


			DATA_TYPE dot( Vector< DATA_TYPE, SIZE > vec2 )
			{
				DATA_TYPE resultVal;
				resultVal = mData[0] * vec2[0] + mData[1] * vec2[1] + mData[2] * vec2[2];
				return resultVal;
			}

			const DATA_TYPE* front()
			{
				return &mData[0];
			}


		private:

			DATA_TYPE mData[SIZE];
	};

	typedef Vector< float, 2 > Vec2f;
	typedef Vector< float, 3 > Vec3f;
	typedef Vector< float, 4 > Vec4f;

	typedef Vector< double, 2 > Vec2d;
	typedef Vector< double, 3 > Vec3d;
	typedef Vector< double, 4 > Vec4d;

	typedef Vector< unsigned int, 2 > Vec2ui;
	typedef Vector< unsigned int, 3 > Vec3ui;
	typedef Vector< unsigned int, 4 > Vec4ui;

	typedef Vector< int, 2 > Vec2i;
	typedef Vector< int, 3 > Vec3i;
	typedef Vector< int, 4 > Vec4i;
}

#endif // __VECTOR_H__