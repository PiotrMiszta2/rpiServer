cmake_minimum_required(VERSION 3.2)
project(raspberry C)
set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "-pthread -Weverything -Wdeclaration-after-statement -Wdate-time")
set(CMAKE_C_FLAGS "-pthread -Wall -pedantic -g")

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR}/server
                    ${INCLUDE_DIR}/util
                    ${INCLUDE_DIR}/messages
                    ${INCLUDE_DIR}/serial
                    ${INCLUDE_DIR}/common_memory)

file(GLOB message_src
        "${SOURCE_DIR}/messages/*.c")
file(GLOB util_src
        "${SOURCE_DIR}/util/*.c")
file(GLOB server_src
        "${SOURCE_DIR}/server/*.c")
file(GLOB serial_src
        "${SOURCE_DIR}/serial/*.c")
file(GLOB common_memory_src
        "${SOURCE_DIR}/common_memory/*.c")

add_executable(raspberry    src/main.c
                            ${message_src}
                            ${util_src}
                            ${server_src}
                            ${serial_src}
                            ${common_memory_src}
)
