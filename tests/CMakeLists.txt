include(CTest)
enable_testing()

function(add_c_file_test test_name)
    add_executable(${test_name} ${CMAKE_CURRENT_SOURCE_DIR}/${test_name}.c)
    target_link_libraries(${test_name} PRIVATE digraph)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

set(DIGRAPH_TESTS
    test_addEdge
    test_removeEdge
    test_isAcyclic
    test_simplify
)

foreach(TEST_NAME IN LISTS DIGRAPH_TESTS)
    add_c_file_test(${TEST_NAME})
endforeach()
