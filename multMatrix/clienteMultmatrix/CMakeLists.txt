cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (client_multMatrix)

add_executable (client_multMatrix main_multMatrix.cpp multmatrix_stub.cpp multmatrix_stub.h utils.h utils.cpp matrix_h.h)

target_link_libraries(client_multMatrix pthread)
