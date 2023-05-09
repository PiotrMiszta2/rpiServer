set(TEST_DIR "${CMAKE_SOURCE_DIR}/test/test_cases")

file(GLOB message_test_src
        "${TEST_DIR}/messages/*.c")

list(APPEND TEST_LIBS "cmocka")
list(APPEND TEST_LIBS "my_test_lib")

list(APPEND TEST_DIRS "${CMOCKA_INCLUDE_DIRS}")
list(APPEND TEST_DIRS "${CMAKE_SOURCE_DIR}/src")

add_cmocka_test(message_test
  SOURCES ${message_test_src}
  COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
  LINK_OPTIONS ${DEFAULT_LINK_FLAGS}
  LINK_LIBRARIES ${TEST_LIBS})
add_cmocka_test_environment(message_test)
target_include_directories(message_test PUBLIC "${TEST_DIRS}")

