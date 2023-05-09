set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB message_hdr
        "${INCLUDE_DIR}/messages/*.h")
file(GLOB util_src
        "${INCLUDE_DIR}/util/*.h")
file(GLOB server_hdr
        "${INCLUDE_DIR}/server/*.h")
file(GLOB serial_hdr
        "${INCLUDE_DIR}/serial/*.h")
file(GLOB common_hdr
        "${INCLUDE_DIR}/common/*.h")

file(GLOB message_src
        "${SOURCE_DIR}/messages/*.c")
file(GLOB util_src
        "${SOURCE_DIR}/util/*.c")
file(GLOB server_src
        "${SOURCE_DIR}/server/*.c")
file(GLOB serial_src
        "${SOURCE_DIR}/serial/*.c")
file(GLOB common_src
        "${SOURCE_DIR}/common/*.c")

add_library(my_test_lib STATIC  ${message_src}
                                ${util_src}
                                ${server_src}
                                ${serial_src}
                                ${common_src}

                                ${message_hdr}
                                ${util_hdr}
                                ${server_hdr}
                                ${serial_hdr}
                                ${common_hdr}
                                )

target_include_directories(my_test_lib PUBLIC    "${INCLUDE_DIR}/messages" "${INCLUDE_DIR}/util"
                                            "${INCLUDE_DIR}/server"
                                            "${INCLUDE_DIR}/serial"
                                            "${INCLUDE_DIR}/common")