#include "Matrix.h"

#define BLOCK_SIZE 16 // Number of threads in the block

__global__ void MatrixMultKernel(const Matrix, const Matrix, Matrix);

void MatrixMult(const Matrix &A, const Matrix &B, Matrix *C)
{
  // Load A and B to device memory
  Matrix d_A;
  d_A.width = A.width;
  d_A.height = A.height;
  size_t size = A.width * A.height * sizeof(float);
  cudaMalloc(&d_A.elements, size);
  cudaMemcpy(d_A.elements, A.elements, size, cudaMemcpyHostToDevice);

  Matrix d_B;
  d_B.width = A.width;
  d_B.height = A.height;
  size = B.width * B.height * sizeof(float);
  cudaMalloc(&d_B.elements, size);
  cudaMemcpy(d_B.elements, A.elements, size, cudaMemcpyHostToDevice);

  Matrix d_C;
  d_C.width = B.width;
  d_C.height = A.height;
  size = C->width * C->height * sizeof(float);
  cudaMalloc(&d_C.elements, size);

  // Invoke kernel
  dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
  dim3 dimGrid(B.width / dimBlock.x, A.height / dimBlock.y);
  MatrixMultKernel<<<dimGrid, dimBlock>>>(d_A, d_B, d_C);

  // Read C from device memory
  cudaMemcpy(C->elements, d_C.elements, size, cudaMemcpyDeviceToHost);

  // Free device memory
  cudaFree(d_A.elements);
  cudaFree(d_B.elements);
  cudaFree(d_C.elements);
}

__global__ void MatrixMultKernel(Matrix A, Matrix B, Matrix C)
{
  // Each thread computes one element of C
  // by accumulating results into Cvalue
  float Cvalue = 0;
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;

  for (int e = 0; e < A.width; ++e)
    Cvalue += A.elements[row * A.width + e] * B.elements[e * B.width + col];

  C.elements[row * C.width + col] = Cvalue;
}

