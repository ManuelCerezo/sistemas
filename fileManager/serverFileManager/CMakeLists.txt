cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (serverFileManager)

add_executable (fileManager main_fm.cpp filemanager.cpp filemanager.h filemanager_imp.cpp filemanager_imp.h serverMain.cpp utils.cpp utils.h)

target_link_libraries(serverFileManager pthread)