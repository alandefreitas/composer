#######################################################
### Catch2 - Unit tests                             ###
#######################################################
# Find or get Catch2
# Note that CPM will try to "find_package(Catch2)" before downloading it
# See the option CPM_USE_LOCAL_PACKAGES in ROOT/CMakeLists.txt
# This is important: see One Definition Rule (ODR)
CPMAddPackage(
        NAME Catch2
        GITHUB_REPOSITORY catchorg/Catch2
        VERSION 2.12.1
        OPTIONS
        "CATCH_USE_VALGRIND OFF"
        "CATCH_BUILD_TESTING OFF"
        "CATCH_BUILD_EXAMPLES OFF"
        "CATCH_BUILD_EXTRA_TESTS OFF"
        "CATCH_ENABLE_COVERAGE OFF"
        "CATCH_ENABLE_WERROR ON"
        "CATCH_INSTALL_DOCS OFF"
        "CATCH_INSTALL_HELPERS OFF"
)
include(${Catch2_SOURCE_DIR}/contrib/Catch.cmake)

#######################################################
### Tests                                           ###
#######################################################

add_executable(ut_melody ut_melody.cpp)
target_link_libraries(ut_melody PUBLIC composerlib Catch2)
catch_discover_tests(ut_melody)

add_executable(ut_midi_stream ut_midi_stream.cpp)
target_link_libraries(ut_midi_stream PUBLIC composerlib Catch2)

set(TEST_RESOURCES
        resources/twinkle_harmonic.mid
        resources/twinkle.midi)

if (MSVC)
    file(COPY ${TEST_RESOURCES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/resources")
else()
    file(COPY ${TEST_RESOURCES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/resources")
endif()
