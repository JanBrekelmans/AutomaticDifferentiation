cmake_minimum_required(VERSION 3.14...3.22)

project(
    Leveque
    VERSION 0.0.1
    LANGUAGES CXX
)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Add dependencies via CPM ----
include(cmake/CPM.cmake)
CPMAddPackage("gh:doctest/doctest@2.4.9")

find_package(doctest REQUIRED)

# ---- Add the matrix library ----
enable_testing()
file(GLOB_RECURSE headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.cpp)
file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

add_library(${PROJECT_NAME} STATIC ${headers} ${sources})

target_include_directories(${PROJECT_NAME}
    PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_link_libraries(${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# ---- Add the main executable ----
add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/application/main.cpp)
target_link_libraries(main ${PROJECT_NAME})
set_property(TARGET main PROPERTY CXX_STANDARD 20)

# ---- Add examples ----
file(GLOB_RECURSE examples CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp)
foreach(example ${examples})
    get_filename_component(CPPNAME ${example} NAME_WE)
    get_filename_component(CPPFOLDER ${example} DIRECTORY)
    get_filename_component(PARENTFOLDER ${CPPFOLDER} NAME_WE)
    string(CONCAT EXAMPLE_NAME ${PARENTFOLDER} "_" ${CPPNAME})
    add_executable(${EXAMPLE_NAME} ${example})
    target_link_libraries(${EXAMPLE_NAME} ${PROJECT_NAME})
    set_target_properties(${EXAMPLE_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
endforeach()

# ---- Add testing ----
set(TEST_PROJECT_NAME ${PROJECT_NAME}Test)
add_executable(${TEST_PROJECT_NAME} ${test_sources})
target_link_libraries(${TEST_PROJECT_NAME} doctest::doctest ${PROJECT_NAME})
set_property(TARGET ${TEST_PROJECT_NAME} PROPERTY CXX_STANDARD 20)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(${TEST_PROJECT_NAME})

# ----Code coverage ----
if(ENABLE_TEST_COVERAGE)
  target_compile_options(${TEST_PROJECT_NAME} PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(${TEST_PROJECT_NAME} PUBLIC -fprofile-arcs -ftest-coverage)
endif()