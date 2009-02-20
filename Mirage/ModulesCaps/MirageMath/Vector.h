
#ifndef __MSG_MATH_VECTOR_H__
#define __MSG_MATH_VECTOR_H__

#include <vector>
#include <math.h>
#include <assert.h>

namespace Mirage
{
  namespace MirageMath
  {
	  template< class DATA_TYPE, unsigned int SIZE >
    class Vector
    {
	    public:
  			
        friend class MatrixVecOps;

        Vector()
		    {
			    for( unsigned int i=0; i < SIZE; ++i )
			    {
				    this->_data[i] = ( DATA_TYPE )0 ;
			    }
		    }


        Vector( const Vector< DATA_TYPE, SIZE >& from )
        {
          for( unsigned i = 0; i < SIZE; ++i )
			    {
            _data[i] = from._data[i];
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

        
        /*template< class TYPE, unsigned int MY_SIZE >
        Vector( Vector< TYPE, MY_SIZE >& vec )
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
              this->_data[i] = DATA_TYPE();
            }
          }
        }
*/

		    ~Vector()
		    {
        }


		    DATA_TYPE& operator[]( unsigned int column )
		    {
			    assert( column < SIZE );
			    return _data[column]; 
		    }


		    const DATA_TYPE& operator[]( unsigned int column ) const
		    {
			    assert( column < SIZE );
			    return _data[column]; 
		    }
  			

		    Vector< DATA_TYPE, SIZE >& operator=( const Vector< DATA_TYPE,SIZE >& rhs )
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


		    bool operator==( const Vector< DATA_TYPE,SIZE >& rhs )
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


		    Vector< DATA_TYPE, SIZE >& operator+=( const Vector< DATA_TYPE,SIZE >& rhs )
		    {
			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    _data[i] = _data[i] + rhs[i];
			    }

			    return *this;
		    }


		    Vector< DATA_TYPE, SIZE >& operator-=( const Vector< DATA_TYPE,SIZE >& rhs )
		    {
			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    _data[i] = _data[i] - rhs[i];
			    }

			    return *this;
		    }


		    Vector< DATA_TYPE, SIZE >& operator*=( const Vector< DATA_TYPE,SIZE >& rhs )
		    {
			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    _data[i] = _data[i] * rhs[i];
			    }

			    return *this;
		    }


		    Vector< DATA_TYPE, SIZE >& operator/=( const Vector< DATA_TYPE,SIZE >& rhs )
		    {
			    for( unsigned i = 0; i < SIZE; ++i )
			    {
				    _data[i] = _data[i] / rhs[i];
			    }

			    return *this;
		    }


		    Vector< DATA_TYPE, SIZE > operator*( DATA_TYPE val )
		    {
			    Vector< DATA_TYPE, SIZE > vec;
			    for( unsigned int i = 0; i < SIZE; ++i )
			    {
				    vec[i] = _data[i] * val;
			    }

			    return vec;
		    }


		    Vector< DATA_TYPE, SIZE > operator+( const Vector< DATA_TYPE,SIZE >& rhs )
		    {
			    Vector< DATA_TYPE, SIZE > vec;
			    for( unsigned int i = 0; i < SIZE; ++i )
			    {
				    vec[i] = _data[i] + rhs[i];
			    }

			    return vec;
		    }


		    Vector< DATA_TYPE, SIZE > operator-( const Vector< DATA_TYPE,SIZE >& rhs )
		    {
			    Vector< DATA_TYPE, SIZE > vec;
			    for( unsigned int i=0; i<SIZE; ++i )
			    {
				    vec[i] = _data[i] - rhs[i];
			    }

			    return vec;
		    }


		    Vector< DATA_TYPE, SIZE > operator/( const Vector< DATA_TYPE, SIZE >& rhs )
		    {
			    Vector< DATA_TYPE, SIZE > vec;
			    for( unsigned int i=0; i<SIZE; ++i )
			    {
				    vec[i] = _data[i] / rhs[i];
			    }

			    return vec;
		    }


		    Vector< DATA_TYPE, SIZE > operator-()
		    {
			    Vector< DATA_TYPE, SIZE > vec;
			    for( unsigned int i=0; i<SIZE; ++i )
			    {
				    vec[i] = -_data[i];
			    }

			    return vec;
		    }			


		    Vector< DATA_TYPE, SIZE >* operator&( const Vector< DATA_TYPE, SIZE >& rhs )
		    {
			    return &rhs[0];
		    }


		    void set( DATA_TYPE val0, DATA_TYPE val1 )
		    {
			    _data[0] = val0;
			    _data[1] = val1;
		    }


		    void set( DATA_TYPE val0, DATA_TYPE val1, DATA_TYPE val2 )
		    {
			    _data[0] = val0;
			    _data[1] = val1;
			    _data[2] = val2;
		    }


		    void set( DATA_TYPE val0, DATA_TYPE val1, DATA_TYPE val2, DATA_TYPE val3 )
		    {
			    _data[0] = val0;
			    _data[1] = val1;
			    _data[2] = val2;
			    _data[3] = val3;
		    }


		    DATA_TYPE length()
		    {
			    DATA_TYPE mVal( 0 );

			    for( unsigned int i = 0; i < SIZE; ++i )
			    {
				    mVal = this->_data[i] * this->_data[i] + mVal;
			    }

          return sqrt( mVal );
		    }


		    Vector< DATA_TYPE, SIZE >& normalize()
		    {
          DATA_TYPE val = length();          

          if( val != DATA_TYPE( 0 ) )
          {
            return *this;
          }

		      for( size_t i=0; i < SIZE; ++i )
		      { 
            _data[i] = _data[i] / val;            
		      }

          return *this;
		    }


		    Vector< DATA_TYPE, SIZE > cross( Vector< DATA_TYPE, SIZE > vec2 )
		    {
			    Vector< DATA_TYPE, SIZE > resultVec;
  				
			    assert( SIZE == 3 );
			    resultVec[0] = ( _data[1] * vec2[2] ) - ( _data[2] * vec2[1] );
			    resultVec[1] = ( _data[2] * vec2[0] ) - ( _data[0] * vec2[2] );
			    resultVec[2] = ( _data[0] * vec2[1] ) - ( _data[1] * vec2[0] );

			    return resultVec;
		    }


		    DATA_TYPE dot( Vector< DATA_TYPE, SIZE > vec2 )
		    {
			    DATA_TYPE resultVal( 0 );
			    
          for( size_t i=0; i < SIZE; ++i )
		      { 
            resultVal = _data[i] * vec2[i] + resultVal;
		      }
          
			    return resultVal;
		    }


		    const DATA_TYPE* front()
		    {
			    return &_data[0];
		    }


        const int& size() const 
        {
          return SIZE;
        }


	    private:

		    DATA_TYPE _data[SIZE];
    };

    typedef Vector< float, 2 >        Vec2f;
    typedef Vector< float, 3 >        Vec3f;
    typedef Vector< float, 4 >        Vec4f;

    typedef Vector< double, 2 >       Vec2d;
    typedef Vector< double, 3 >       Vec3d;
    typedef Vector< double, 4 >       Vec4d;

    typedef Vector< unsigned int, 2 > Vec2ui;
    typedef Vector< unsigned int, 3 > Vec3ui;
    typedef Vector< unsigned int, 4 > Vec4ui;

    typedef Vector< int, 2 >          Vec2i;
    typedef Vector< int, 3 >          Vec3i;
    typedef Vector< int, 4 >          Vec4i;
  }
}

#endif // __MSG_MATH_VECTOR_H__
