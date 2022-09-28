# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

project ("C++_CMAKE_Learning")

# Include sub-projects.
add_subdirectory ("app")
add_subdirectory ("engine")
