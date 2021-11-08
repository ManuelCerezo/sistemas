cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (client_FileManager)

add_executable (client_FileManager main_fm.cpp filemanager_stub.cpp local_env.cpp local_env.h filemanager_stub.h utils.cpp utils.h)

target_link_libraries(client_FileManager pthread)
