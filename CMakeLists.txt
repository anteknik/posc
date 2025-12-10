cmake_minimum_required(VERSION 3.5)
project(ProyekSaya VERSION 0.1.0)

# Standar C++ (Opsional, tapi disarankan)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Menghubungkan file source ke executable
# Include header files from library directory
include_directories(library)

# Gather all source files
file(GLOB SOURCES "src/*.cpp")

# Create executable (WIN32 for GUI)
add_executable(ProyekSaya WIN32 ${SOURCES})

# Link Windows libraries
target_link_libraries(ProyekSaya gdi32 user32)
