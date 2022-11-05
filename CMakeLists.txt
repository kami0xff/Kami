# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

project ("Kami")

# Include sub-projects.
add_subdirectory ("kami")
add_subdirectory ("kamiEngine")
