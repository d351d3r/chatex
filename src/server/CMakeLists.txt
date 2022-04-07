cmake_minimum_required(VERSION 3.20)

include_directories(headers)
include_directories(structs)

add_library(server_handlers STATIC replies.cpp)
add_library(server STATIC Server.cpp)
add_library(server_storages STATIC storages.cpp)
target_include_directories(server_handlers PUBLIC headers)
target_include_directories(server PUBLIC structs)

target_link_libraries(server_handlers contrib_json)
target_link_libraries(server server_handlers)
target_link_libraries(server server_storages)

add_executable(server_starter server_runner.cpp)

target_link_libraries(server_starter server)
target_compile_options(server_starter PRIVATE -std=c++17)
target_compile_definitions(server_starter PRIVATE BOOST_ERROR_CODE_HEADER_ONLY)
target_link_libraries(server_starter pthread)
