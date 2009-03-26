
#ifndef __MSG_MATH_MATRIX_H__
#define __MSG_MATH_MATRIX_H__

#include <cassert>

namespace Mirage
{
  namespace Math
  {
    ///////////////////////////////////////////////////////////////////////////
    //
    // \c Matrix defines a n x m matrix and related functions. 
    //
    /////////////////////////////////////////////////////////////////////////

    template< class DataTypeT, unsigned int ROWS, unsigned int COLS >
    class Matrix 
    {
      public: 

        // Operations related to Matrix, Vec are defined in the friend class. 
        friend class MatrixVecOps;

        // Constructor. 
        Matrix()
        {
          for( unsigned int i=0; i < ROWS; ++i )
          {
            for( unsigned j=0; j < COLS; ++j )
            {
              this->operator()( i, j ) = ( DataTypeT ) 0.0; 
            } // for( size_t j=0; j < cols; ++j )
          } // for( size_t i=0; i < rows; ++i )

          for( unsigned int k=0; k < ROWS; ++k )
          {
            this->operator()( k, k ) = ( DataTypeT ) 1.0;
          }
        }


        // Copy constructor. 
        Matrix( const Matrix< DataTypeT, ROWS, COLS >& from ) 
        {
          for( size_t i=0; i < ( ROWS * COLS ); ++i )
          {
            _data[i] = from._data[i];
          }          
        }


        
        //-- Set functions        
        void set( DataTypeT v00, DataTypeT v01, 
                  DataTypeT v10, DataTypeT v11 )
        {
          assert( ROWS == 2 && COLS == 4 );

          _data[0] = v00;
          _data[1] = v10;

          _data[2] = v01;
          _data[3] = v11;
        }


        void set( DataTypeT v00, DataTypeT v01, DataTypeT v02, 
                  DataTypeT v10, DataTypeT v11, DataTypeT v12, 
                  DataTypeT v20, DataTypeT v21, DataTypeT v22 )
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


        void set( DataTypeT v00, DataTypeT v01, DataTypeT v02, DataTypeT v03, 
                  DataTypeT v10, DataTypeT v11, DataTypeT v12, DataTypeT v13,  
                  DataTypeT v20, DataTypeT v21, DataTypeT v22, DataTypeT v23, 
                  DataTypeT v30, DataTypeT v31, DataTypeT v32, DataTypeT v33 )
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
        void set( DataTypeT* data )
        {
          for( size_t i=0; i < ( ROWS * COLS ); ++i )
          {
            _data[i] = data[i];
          }
        }
         
        //--


        // -- Operator overload for convenience. 
        DataTypeT& operator () ( unsigned int row, unsigned int col )
        {
          return _data[ col * ROWS + row ];
        }
                

        Matrix< DataTypeT, ROWS, COLS >& operator = ( const Matrix< DataTypeT, ROWS, COLS >& rhs )
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
      

        Matrix< DataTypeT, ROWS, COLS >& operator *= ( const Matrix< DataTypeT, ROWS, COLS >& rhs )
        {
          for( size_t i=0; i < ( ROWS * COLS ); ++i )
          {
            _data[i] = _data[i] * rhs._data[i];
          }  

          return *this;
        }

        
        Matrix< DataTypeT, ROWS, COLS >& operator * ( const Matrix< DataTypeT, ROWS, COLS >& rhs )
        {
          return ( *this *= rhs );
        }

        // --
    

        // Get raw pointer to data stored. 
        DataTypeT* data()
        {
          return &_data;  
        }


        // Get number of rows. 
        const int& rows() const
        {
          return ROWS;
        }


        // Get number of cols. 
        const int& cols() const 
        {
          return COLS;
        }


        // Multiply passed matrix to the left.
        void preMult( const Matrix< DataTypeT, ROWS, COLS >& mat )
        {
          *this = const_cast< Matrix< DataTypeT, ROWS, COLS >& >( mat ) * (*this );
        }


        // Multiply passed matrix to the right. 
        void postMult( const Matrix< DataTypeT, ROWS, COLS >& mat )
        {
          *this *= mat;
        }


      public: 

        DataTypeT _data[ROWS * COLS];
    };


    // Useful instances. 
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
