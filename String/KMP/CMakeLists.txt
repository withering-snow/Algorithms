add_executable(kmp
    current.cpp
    test.cpp
)

target_include_directories(kmp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test(
    NAME KMP
    COMMAND kmp
)
