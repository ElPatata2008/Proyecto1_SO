#include "../include/alpha_kernels.hpp"
#include <cuda_runtime.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>

namespace pipeline {
    struct DeviceBuffer {
        float* ptr = nullptr;
        DeviceBuffer() = default;
        DeviceBuffer(const DeviceBuffer&) = delete;
        DeviceBuffer& operator=(const DeviceBuffer&) = delete;
        ~DeviceBuffer() { if (ptr) cudaFree(ptr); }
    };
    
    bool cudaOk(cudaError_t err, const char* what) {
        if (err == cudaSuccess) return true;
        std::fprintf(stderr, "CUDA error en %s: %s\n", what, cudaGetErrorString(err));
        return false;
    }
}
    
__global__ void rotateYKernel(float* data, int n, float c, float s) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n){ 
        auto x = data[3 * i]; 
        auto z = data[3 * i + 2];
        data[3 * i]     =  x * c + z * s;
        data[3 * i + 2] = -x * s + z * c;
    }
}

bool transformMesh(float* dataCPU, int n, float angle) {

    size_t bytes = 3 * n * sizeof(float);
    pipeline::DeviceBuffer dev;

    // Reserva Memoría en la GPU
    if (!pipeline::cudaOk(cudaMalloc(&dev.ptr, bytes), "cudaMalloc")) return false;
    // CUDA_CHECK(cudaMalloc(&dataGPU, bytes));

    // Copia de datos de la CPU a la GPU
    if (!pipeline::cudaOk(cudaMemcpy(dev.ptr, dataCPU, bytes, cudaMemcpyHostToDevice), "cudaMemcpy CPU to GPU")) return false;

    // Lanzamiento
    int t = 256;
    int b = (n + t - 1) / t; 
    auto c = std::cos(angle);
    auto s = std::sin(angle);
    rotateYKernel<<<b, t>>>(dev.ptr, n, c, s); 

    // Informa si el lanzamiento falló
    if (!pipeline::cudaOk(cudaGetLastError(), "cudaGetLastError")) return false;

    // Copia de datos de la GPU a la CPU
    if (!pipeline::cudaOk(cudaMemcpy(dataCPU, dev.ptr, bytes, cudaMemcpyDeviceToHost), "cudaMemcpy GPU to CPU")) return false;

    // Libera la reserva de memoria en la GPU
    return true;
}