#pragma once

void transformMesh(std::vector<float> data, int n);
__global__ void kernel(float* data, int n);