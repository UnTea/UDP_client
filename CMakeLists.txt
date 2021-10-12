cmake_minimum_required(VERSION 3.21)
project(udp_client)

set(CMAKE_CXX_STANDARD 20)

add_executable(udp_client main.cpp )
target_link_libraries(udp_client ws2_32.lib)
