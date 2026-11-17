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
            std::exit(1);                                          \
        }                                                          \
    } while (0)

__global__ void addOne(float* data, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) data[i] += 1.0f;
}

int main() {
    const int n = 1000;
    std::vector<float> host(n, 0.0f);

    float* dev = nullptr;
    CUDA_CHECK(cudaMalloc(&dev, n * sizeof(float)));
    CUDA_CHECK(cudaMemcpy(dev, host.data(), n * sizeof(float),
                          cudaMemcpyHostToDevice));

    int threads = 256;
    int blocks  = (n + threads - 1) / threads;   // división hacia arriba
    addOne<<<blocks, threads>>>(dev, n);
    CUDA_CHECK(cudaGetLastError());

    CUDA_CHECK(cudaMemcpy(host.data(), dev, n * sizeof(float),
                          cudaMemcpyDeviceToHost));
    CUDA_CHECK(cudaFree(dev));

    std::printf("host[0]=%.1f host[999]=%.1f\n", host[0], host[999]);
}