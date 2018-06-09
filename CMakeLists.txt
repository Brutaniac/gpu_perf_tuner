cmake_minimum_required(VERSION 3.0)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.21.5.tar.gz"
    SHA1 "c5c1803ee355efc952fd455f6d1f2fc24b9f5087"
)

project(gpu_perf_tuner)

hunter_add_package(Boost COMPONENTS system program_options)

find_package(Boost CONFIG REQUIRED system  program_options)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wpedantic -Werror")

add_executable(${PROJECT_NAME}
    main.cpp
    utils/utils.cpp
    devices/device_management.cpp
    devices/amd_rocm/amd_rocm_gpu.cpp
    devices/controllers.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Boost::system
    Boost::program_options
    pthread
)
