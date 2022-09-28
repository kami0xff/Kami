# CMakeList.txt : CMake project for C++_CMAKE_Learning, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

# Add source to this project's executable.
add_executable (app "main.cpp")
set_property(TARGET app PROPERTY CXX_STANDARD 20)

target_include_directories(app PRIVATE engine)
target_link_libraries(app PRIVATE engine)

# TODO: Add tests and install targets if needed.
