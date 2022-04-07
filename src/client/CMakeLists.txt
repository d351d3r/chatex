cmake_minimum_required(VERSION 3.20)

include_directories(handlers)
include_directories(structs)

add_library(talker_helper STATIC talk_helper.cpp)
add_library(client STATIC Client.cpp)
target_include_directories(talker_helper PUBLIC handlers)
target_include_directories(client PUBLIC structs)

target_link_libraries(talker_helper contrib_json)
target_link_libraries(client talker_helper)

add_executable(client_starter client_starter.cpp)

target_link_libraries(client_starter client)
target_compile_options(client_starter PRIVATE -std=c++17)
target_compile_definitions(client_starter PRIVATE BOOST_ERROR_CODE_HEADER_ONLY)
target_link_libraries(client_starter pthread boost_thread)
