cmake_minimum_required(VERSION 3.16)
project(sqlite_cpp_app C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)

FetchContent_Declare(
  sqlite3
  URL https://www.sqlite.org/2024/sqlite-amalgamation-3460000.zip
)
FetchContent_MakeAvailable(sqlite3)

# Define sqlite3 library from fetched sources if not already defined
if(NOT TARGET sqlite3)
    add_library(sqlite3 STATIC ${sqlite3_SOURCE_DIR}/sqlite3.c)
    target_include_directories(sqlite3 PUBLIC ${sqlite3_SOURCE_DIR})
    # Linux might need dl token thread
    if(UNIX AND NOT APPLE)
        target_link_libraries(sqlite3 PRIVATE dl pthread)
    endif()
endif()

add_executable(app 
    src/main.cpp
    src/database/Database.cpp
    src/repositories/ProductRepository.cpp
    src/repositories/OrderRepository.cpp
    src/services/PosService.cpp
)
target_link_libraries(app PRIVATE sqlite3)
