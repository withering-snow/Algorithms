add_executable(avl
    current.cpp
    test.cpp
)

target_include_directories(avl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test(
    NAME AVL
    COMMAND avl
)
