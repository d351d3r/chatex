cmake_minimum_required(VERSION 3.20)
project(Chat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
        CACHE STRING "Compiler flags in asan build"
        FORCE
        )
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2")

find_package(JSON 3.2.0 REQUIRED)

include_directories(libraries/include)

add_subdirectory(src/server)
link_directories(src/server)

add_subdirectory(src/client)
link_directories(src/client)
