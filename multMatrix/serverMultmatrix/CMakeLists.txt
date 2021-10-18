cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (server_multMatrix)

add_executable (server_multMatrix serverMain.cpp multmatrix_imp.cpp multmatrix_imp.h multmatrix.cpp multmatrix.h utils.h utils.cpp matrix_h.h)

target_link_libraries(server_multMatrix pthread)
