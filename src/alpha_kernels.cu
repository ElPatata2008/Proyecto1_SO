#include "../include/alpha_kernels.hpp"
#include <cuda_runtime.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#define CUDA_CHECK(call)                                           \
    do {                                                           \
        cudaError_t err = (call);                                  \
        if (err != cudaSuccess) {                                  \
            std::fprintf(stderr, "CUDA error: %s (línea %d)\n",    \
                         cudaGetErrorString(err), __LINE__);       \
        }                                                          \
    } while (0)

void transformMesh(std::vector<float> dataCPU, int n) {

    size_t bytes = n * sizeof(float);
    float* dataGPU = nullptr;

    // Reserva Memoría en la GPU
    CUDA_CHECK(cudaMalloc(&dataGPU, bytes));

    // Copia de datos de la CPU a la GPU
    CUDA_CHECK(cudaMemcpy(dataGPU, dataCPU.data(), bytes, cudaMemcpyHostToDevice));

    // Lanzamiento del kernel
    int t = 256;
    int b = (n + t - 1) / t; // división hacia arriba
    kernel<<<b, t>>>(dataGPU, n); 

    // Informa si el lanzamiento falló
    CUDA_CHECK(cudaGetLastError());

    // Copia de datos de la GPU a la CPU
    CUDA_CHECK(cudaMemcpy(dataCPU.data(), dataGPU, bytes, cudaMemcpyDeviceToHost));

    // Libera la reserva de memoria en la GPU
    CUDA_CHECK(cudaFree(dataGPU));
}

__global__ void kernel(float* data, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) data[i] += 1.0f; 
}