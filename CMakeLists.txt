CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(FDTD_solver)

FIND_PACKAGE(CUDA REQUIRED)

INCLUDE(FindCUDA)

SET(CUDA_SEPARABLE_COMPILATION ON)

INCLUDE_DIRECTORIES(/usr/local/cuda/include)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cu" "src/*.h")
CUDA_ADD_EXECUTABLE(FDTD_Solver ${SOURCES})

LIST(APPEND CMAKE_CXX_FLAGS "-std=c++11 -O3 -ffast-math -Wall")

LIST(APPEND CUDA_NVCC_FLAGS --compiler-options  -fno-strict-aliasing -lineinfo -use_fast_math -Xptxas -dlcm=cg)
LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_20,code=sm_20)
LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_30,code=sm_30)
LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_35,code=sm_35)
