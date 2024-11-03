enable_testing()

# Fetch doctest
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY "https://github.com/onqtam/doctest"
    GIT_TAG "ae7a13539fb71f270b87eb2e874fbac80bc8dda2"
)
FetchContent_MakeAvailable(doctest)

# Create test executable
add_executable(tests 
    ${PROJECT_SOURCE_DIR}/tests/tests.cpp
    interval.cpp
    helpers.cpp
)

# Include doctest cmake utilities
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)

# Link against both doctest and spacely
target_link_libraries(tests 
    PRIVATE 
        doctest
        spacely
)

# Make sure tests can find spacely headers
target_include_directories(tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Add post-build commands to copy DLLs next to the test executable
add_custom_command(TARGET tests POST_BUILD
    # Copy spacely DLL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:spacely>
        $<TARGET_FILE_DIR:tests>
)

# Discover and add tests
doctest_discover_tests(tests)

# Register test
add_test(NAME tests COMMAND tests)