
#ifndef __MSG_MATH_VECTOR_H__
#define __MSG_MATH_VECTOR_H__

#include <vector>
#include <math.h>
#include <assert.h>

namespace Mirage
{
  namespace Math
  {
	  template< class DataTypeT, unsigned int SIZE >
    class Vec
    {
	    public:
  			
        friend class MatrixVecOps;

        Vec()
		    {
			    for( unsigned int i=0; i < SIZE; ++i )
			    {
				    this->_data[i] = ( DataTypeT )0 ;
			    }
		    }


        Vec( const Vec< DataTypeT, SIZE >& from )
        {
          for( unsigned i = 0; i < SIZE; ++i )
			    {
            _data[i] = from._data[i];
			    }
        }


		    Vec( DataTypeT val0, DataTypeT val1 )
		    {
			    Vec();
			    set( val0, val1 );
		    }


		    Vec( DataTypeT val0, DataTypeT val1, DataTypeT val2 )
		    {
			    Vec();
			    set( val0, val1, val2 );
		    }


		    Vec( DataTypeT val0, DataTypeT val1, DataTypeT val2, DataTypeT val3 )
		    {
			    Vec();
			    set( val0, val1, val2, val3 );
		    }

        
        /*template< class TYPE, unsigned int MY_SIZE >
        Vec( Vec< TYPE, MY_SIZE >& vec )
        {
          for( size_t i=0; i < vec.size(); ++i )
          {
            if( i < SIZE )
            {
              this->_data[i] = vec[i];
            }
          }
          
          if( vec.size() < SIZE )
          {
            for( size_t i= vec.size(); i < SIZE; ++i )
            {
              this->_data[i] = DataTypeT();
            }
          }
        }
*/

		    ~Vec()
		    {
        }


		    DataTypeT& operator[]( unsigned int column )
		    {
			    assert( column < SIZE );
			    return _data[column]; 
		    }


		    const DataTypeT& operator[]( unsigned int column ) const
		    {
			    assert( column < SIZE );
			    return _data[column]; 
		    }
  			

		    Vec< DataTypeT, SIZE >& operator=( const Vec< DataTypeT,SIZE >& rhs )
		    {
          if( &rhs == this )
          {
            return *this;
          }

			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    _data[i] = rhs[i];
			    }

			    return *this;
		    }


		    bool operator==( const Vec< DataTypeT,SIZE >& rhs )
		    {
			    bool retVal = true;

			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    if( _data[i] != rhs[i] )
				    {
					    retVal = false;
				    }
			    }

			    return retVal;				
		    }


		    Vec< DataTypeT, SIZE >& operator+=( const Vec< DataTypeT,SIZE >& rhs )
		    {
			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    _data[i] = _data[i] + rhs[i];
			    }

			    return *this;
		    }


		    Vec< DataTypeT, SIZE >& operator-=( const Vec< DataTypeT,SIZE >& rhs )
		    {
			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    _data[i] = _data[i] - rhs[i];
			    }

			    return *this;
		    }


		    Vec< DataTypeT, SIZE >& operator*=( const Vec< DataTypeT,SIZE >& rhs )
		    {
			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    _data[i] = _data[i] * rhs[i];
			    }

			    return *this;
		    }


		    Vec< DataTypeT, SIZE >& operator/=( const Vec< DataTypeT,SIZE >& rhs )
		    {
			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    _data[i] = _data[i] / rhs[i];
			    }

			    return *this;
		    }


		    Vec< DataTypeT, SIZE > operator*( DataTypeT val )
		    {
			    Vec< DataTypeT, SIZE > vec;
			    for( unsigned int i = 0; i < SIZE; ++i )
			    {
				    vec[i] = _data[i] * val;
			    }

			    return vec;
		    }


		    Vec< DataTypeT, SIZE > operator+( const Vec< DataTypeT,SIZE >& rhs )
		    {
			    Vec< DataTypeT, SIZE > vec;
			    for( unsigned int i = 0; i < SIZE; ++i )
			    {
				    vec[i] = _data[i] + rhs[i];
			    }

			    return vec;
		    }


		    Vec< DataTypeT, SIZE > operator-( const Vec< DataTypeT,SIZE >& rhs )
		    {
			    Vec< DataTypeT, SIZE > vec;
			    for( unsigned int i=0; i<SIZE; ++i )
			    {
				    vec[i] = _data[i] - rhs[i];
			    }

			    return vec;
		    }


		    Vec< DataTypeT, SIZE > operator/( const Vec< DataTypeT, SIZE >& rhs )
		    {
			    Vec< DataTypeT, SIZE > vec;
			    for( unsigned int i=0; i<SIZE; ++i )
			    {
				    vec[i] = _data[i] / rhs[i];
			    }

			    return vec;
		    }


		    Vec< DataTypeT, SIZE > operator-()
		    {
			    Vec< DataTypeT, SIZE > vec;
			    for( unsigned int i=0; i<SIZE; ++i )
			    {
				    vec[i] = -_data[i];
			    }

			    return vec;
		    }			


		    Vec< DataTypeT, SIZE >* operator&( const Vec< DataTypeT, SIZE >& rhs )
		    {
			    return &rhs[0];
		    }


		    void set( DataTypeT val0, DataTypeT val1 )
		    {
			    _data[0] = val0;
			    _data[1] = val1;
		    }


		    void set( DataTypeT val0, DataTypeT val1, DataTypeT val2 )
		    {
			    _data[0] = val0;
			    _data[1] = val1;
			    _data[2] = val2;
		    }


		    void set( DataTypeT val0, DataTypeT val1, DataTypeT val2, DataTypeT val3 )
		    {
			    _data[0] = val0;
			    _data[1] = val1;
			    _data[2] = val2;
			    _data[3] = val3;
		    }


		    DataTypeT length()
		    {
			    DataTypeT mVal( 0 );

			    for( unsigned int i = 0; i < SIZE; ++i )
			    {
				    mVal = this->_data[i] * this->_data[i] + mVal;
			    }

          return sqrt( mVal );
		    }


		    Vec< DataTypeT, SIZE >& normalize()
		    {
          DataTypeT val = length();          

          if( val != DataTypeT( 0 ) )
          {
            return *this;
          }

		      for( size_t i=0; i < SIZE; ++i )
		      { 
            _data[i] = _data[i] / val;            
		      }

          return *this;
		    }


		    Vec< DataTypeT, SIZE > cross( Vec< DataTypeT, SIZE > vec2 )
		    {
			    Vec< DataTypeT, SIZE > resultVec;
  				
			    assert( SIZE == 3 );
			    resultVec[0] = ( _data[1] * vec2[2] ) - ( _data[2] * vec2[1] );
			    resultVec[1] = ( _data[2] * vec2[0] ) - ( _data[0] * vec2[2] );
			    resultVec[2] = ( _data[0] * vec2[1] ) - ( _data[1] * vec2[0] );

			    return resultVec;
		    }


		    DataTypeT dot( Vec< DataTypeT, SIZE > vec2 )
		    {
			    DataTypeT resultVal( 0 );
			    
          for( unsigned int i=0; i < SIZE; ++i )
		      { 
            resultVal = _data[i] * vec2[i] + resultVal;
		      }
          
			    return resultVal;
		    }


		    const DataTypeT* front()
		    {
			    return &_data[0];
		    }


        const int& size() const 
        {
          return SIZE;
        }


	    public:

		    DataTypeT _data[SIZE];
    };

    typedef Vec< float, 2 >        Vec2f;
    typedef Vec< float, 3 >        Vec3f;
    typedef Vec< float, 4 >        Vec4f;

    typedef Vec< double, 2 >       Vec2d;
    typedef Vec< double, 3 >       Vec3d;
    typedef Vec< double, 4 >       Vec4d;

    typedef Vec< unsigned int, 2 > Vec2ui;
    typedef Vec< unsigned int, 3 > Vec3ui;
    typedef Vec< unsigned int, 4 > Vec4ui;

    typedef Vec< int, 2 >          Vec2i;
    typedef Vec< int, 3 >          Vec3i;
    typedef Vec< int, 4 >          Vec4i;
  }
}

#endif // __MSG_MATH_VECTOR_H__
