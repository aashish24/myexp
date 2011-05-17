#include <stdio.h>

#include <time.h>

void cVecAdd(float *A, float *B, float *C)
{
  for(long long i=0; i < (4096 * 16); ++i)
  {
    C[i] = A[i] + B[i];
  }
}

__global__ void VecAdd(float *A, float *B, float *C)
{
  long long i = threadIdx.x + blockIdx.x * blockDim.x;
  C[i] = A[i] + B[i];
}

int main()
{
  const long long N = 4096 * 16;
  dim3 NumberOfThreadsPerBlock (16, 16, 1);
  dim3 NumberOfBlocks  ((N / NumberOfThreadsPerBlock.x), 
                        (N / NumberOfThreadsPerBlock.y), 
                        1);
  
  //printf("Number of blocks %d ", NumberOfBlocks);
  
  float A[N];
  float B[N];
  float C[N];

  float *D_A, *D_B, *D_C;

  clock_t start, end, cstart, cend;
  double elapsed, celapsed;

  size_t memSize = N * sizeof(float);
  cudaMalloc( (void**) &D_A, memSize);
  cudaMalloc( (void**) &D_B, memSize);
  cudaMalloc( (void**) &D_C, memSize);

  for(long long i=0; i < N; ++i)
  {
    A[i] = i;
    B[i] = i * 2.0;
    C[i] = 0;
  }

  cudaMemcpy(D_A, A, memSize, cudaMemcpyHostToDevice);
  cudaMemcpy(D_B, B, memSize, cudaMemcpyHostToDevice);
  cudaMemcpy(D_C, C, memSize, cudaMemcpyHostToDevice);  

  cudaThreadSynchronize();
  start = clock();

  VecAdd<<<NumberOfBlocks, NumberOfThreadsPerBlock>>>(D_A, D_B, D_C);

  cudaThreadSynchronize();

  cudaMemcpy(C, D_C, memSize, cudaMemcpyDeviceToHost);
  end = clock();

  elapsed = ((double)(end-start)) / CLOCKS_PER_SEC;  

  for(long i=0; i < N; ++i)
  {
    printf("%f \n", C[i]);
  }

  cstart = clock();
  printf("clock start %f ", cstart);
  cVecAdd(A, B, C);
  cend = clock();
  printf("clock end %f ", cend);
  celapsed = ((double)(cend - cstart)) / CLOCKS_PER_SEC;

  printf("Time elapsed %f ", elapsed);
  printf("Time celapsed %f ", celapsed);

  cudaFree(D_A);
  cudaFree(D_B);
  cudaFree(D_C);
}

