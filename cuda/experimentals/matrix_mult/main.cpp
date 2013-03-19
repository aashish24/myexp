#include "Matrix.h"

#include <cstdio>

extern void MatrixMult(const Matrix &A, const Matrix &B, Matrix *C);

int main(int argc, char **argv)
{
  Matrix A;
  Matrix B;
  Matrix C;

  A.height = 4;
  A.width = 4;

  B.height = 4;
  B.width = 4;

  C.height = 4;
  C.width = 4;

  A.elements = new float[16];
  B.elements = new float[16];
  C.elements = new float[16];

  for(int i = 0; i < 16; ++i)
  {
    A.elements[i] = 1;
  }

  for(int i = 0; i < 16; ++i)
  {
    B.elements[i] = 2;
  }

  for(int i = 0; i < 16; ++i)
  {
    C.elements[i] = 0;
  }

  MatrixMult(A, B, &C);

  for(int i = 0; i < 16; ++i)
  {
    printf("C elements %f \n", C.elements[i]);
  }

  return 0;
}
