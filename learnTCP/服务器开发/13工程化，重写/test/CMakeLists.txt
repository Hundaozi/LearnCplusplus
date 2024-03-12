cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Pine
        VERSION 0.1
        DESCRIPTION "pine"
        LANGUAGES C CXX
)
file(GLOB PINE_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")

# #####################################################################################################################
# DEPENDENCIES
# #####################################################################################################################

# #####################################################################################################################
# MAKE TARGETS
# #####################################################################################################################

# #########################################
# "make check-tests"
# #########################################
add_custom_target(build-tests COMMAND ${CMAKE_CTEST_COMMAND} --show-only)
add_custom_target(check-tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

# #########################################
# "make server client ..."
# #########################################
foreach(pine_test_source ${PINE_TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(pine_test_filename ${pine_test_source} NAME)
    string(REPLACE ".cpp" "" pine_test_name ${pine_test_filename})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${pine_test_name} EXCLUDE_FROM_ALL ${pine_test_source})
    add_dependencies(build-tests ${pine_test_name})
    add_dependencies(check-tests ${pine_test_name})

    target_link_libraries(${pine_test_name} pine_shared)

    # Set test target properties and dependencies.
    set_target_properties(${pine_test_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        COMMAND ${pine_test_name}
    )
endforeach(pine_test_source ${PINE_TEST_SOURCES})