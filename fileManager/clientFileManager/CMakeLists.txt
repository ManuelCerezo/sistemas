cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (clientFileManager)

add_executable (fileManager main_fm.cpp filemanager_stub.cpp filemanager_stub.h utils.cpp utils.h)

target_link_libraries(clientFileManager pthread)