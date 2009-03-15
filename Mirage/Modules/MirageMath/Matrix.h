
#ifndef __MSG_MATH_MATRIX_H__
#define __MSG_MATH_MATRIX_H__

#include <cassert>

namespace Mirage
{
  namespace MirageMath
  {
    template< class DATA_TYPE, unsigned int ROWS, unsigned int COLS >
    class Matrix 
    {
      public: 

        friend class MatrixVecOps;

        Matrix()
        {
          for( unsigned int i=0; i < ROWS; ++i )
          {
            for( unsigned j=0; j < COLS; ++j )
            {
              this->operator()( i, j ) = ( DATA_TYPE ) 0.0; 
            } // for( size_t j=0; j < cols; ++j )
          } // for( size_t i=0; i < rows; ++i )

          for( unsigned int k=0; k < ROWS; ++k )
          {
            this->operator()( k, k ) = ( DATA_TYPE ) 1.0;
          }
        }


        Matrix( const Matrix< DATA_TYPE, ROWS, COLS >& from ) 
        {
          for( size_t i=0; i < ( ROWS * COLS ); ++i )
          {
            _data[i] = from._data[i];
          }          
        }


        void set( DATA_TYPE v00, DATA_TYPE v01, 
                  DATA_TYPE v10, DATA_TYPE v11 )
        {
          assert( ROWS == 2 && COLS == 4 );

          _data[0] = v00;
          _data[1] = v10;

          _data[2] = v01;
          _data[3] = v11;
        }


        void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02, 
                  DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12, 
                  DATA_TYPE v20, DATA_TYPE v21, DATA_TYPE v22 )
        {
          assert( ROWS == 3 && COLS == 3 );

          _data[0] = v00;
          _data[1] = v10;
          _data[2] = v20;
          
          _data[3] = v01;
          _data[4] = v11;
          _data[5] = v21;
          
          _data[6] = v01;
          _data[7] = v12;
          _data[8] = v22;
        }


        void set( DATA_TYPE v00, DATA_TYPE v01, DATA_TYPE v02, DATA_TYPE v03, 
                  DATA_TYPE v10, DATA_TYPE v11, DATA_TYPE v12, DATA_TYPE v13,  
                  DATA_TYPE v20, DATA_TYPE v21, DATA_TYPE v22, DATA_TYPE v23, 
                  DATA_TYPE v30, DATA_TYPE v31, DATA_TYPE v32, DATA_TYPE v33 )
        {
          assert( ROWS == 4 && COLS == 4 );

          _data[0] = v00;
          _data[1] = v10;
          _data[2] = v20;        
          _data[3] = v30;

          _data[4] = v01;
          _data[5] = v11;        
          _data[6] = v21;
          _data[7] = v31;

          _data[8] = v02;
          _data[9] = v12;
          _data[10] = v22;
          _data[11] = v32;

          _data[12] = v03;
          _data[13] = v13;
          _data[14] = v23;
          _data[15] = v33;
        }


        // Input data represent colom major matrix in this case. 
        void set( DATA_TYPE* data )
        {
          for( size_t i=0; i < ( ROWS * COLS ); ++i )
          {
            _data[i] = data[i];
          }
        }

        
        DATA_TYPE& operator()( unsigned int row, unsigned int col )
        {
          return _data[ col * ROWS + row ];
        }
        

        Matrix< DATA_TYPE, ROWS, COLS >& operator=( const Matrix< DATA_TYPE, ROWS, COLS >& rhs )
        {
          if( &rhs == this )
          {
            return *this;
          }

          for( size_t i=0; i < ( ROWS * COLS ); ++i )
          {
            _data[i] = rhs._data[i];
          }

          return *this;
        }


        DATA_TYPE* data()
        {
          return &_data;  
        }


        const int& rows() const
        {
          return ROWS;
        }


        const int& cols() const 
        {
          return COLS;
        }


      public: 

        DATA_TYPE _data[ROWS * COLS];
    };


    typedef Matrix< int, 2, 2 >     Matrix22i;
    typedef Matrix< int, 3, 3 >     Matrix33i;
    typedef Matrix< int, 4, 4 >     Matrix44i;
    
    typedef Matrix< float, 2, 2 >   Matrix22f;
    typedef Matrix< float, 3, 3 >   Matrix33f;
    typedef Matrix< float, 4, 4 >   Matrix44f;

    typedef Matrix< double, 2, 2 >  Matrix22d;
    typedef Matrix< double, 3, 3 >  Matrix33d;
    typedef Matrix< double, 4, 4 >  Matrix44d;
  }
}

#endif // __MSG_MATH_MATRIX_H__
