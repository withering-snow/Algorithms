add_executable(fast_transpose
    current.cpp
    test.cpp
)

target_include_directories(fast_transpose PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test(
    NAME FastTranspose
    COMMAND fast_transpose
)
