cmake_minimum_required(VERSION 3.10)

project(Lekplats VERSION 0.0.1.0
                 DESCRIPTION "Just my personal playground"
                 LANGUAGES CXX)

### External dependencies

find_package(Qt5 5.10 REQUIRED QUIET 
                      COMPONENTS Gui)

### Internal dependencies

include("cmake/setup_library.cmake")

setup_library(LIB_NAME basics
              HEADERS include/point2D.h include/point2D_utils.h
              SOURCES src/point2D_utils.cpp)

setup_library(LIB_NAME algorithms
              HEADERS include/kmeans.h include/van_eck_sequence.h
              SOURCES src/kmeans.cpp src/van_eck_sequence.cpp
              DEPENDENCIES basics)

# XXX: Not sure chaos game should be here, but that works for now
setup_library(LIB_NAME synthdata
              HEADERS include/cluster_generator.h include/chaos_game.h
              SOURCES src/cluster_generator.cpp src/chaos_game.cpp
              DEPENDENCIES basics)

setup_library(LIB_NAME visualization
              HEADERS include/image_io.h
              SOURCES src/image_io.cpp
              DEPENDENCIES Qt5::Gui basics)

### Executables

include("cmake/setup_app.cmake")

setup_app(APP_NAME van_eck DEPENDENCIES algorithms)
setup_app(APP_NAME chaos DEPENDENCIES synthdata visualization)
setup_app(APP_NAME kmeans DEPENDENCIES algorithms synthdata visualization)
setup_app(APP_NAME cellular_automata DEPENDENCIES Qt5::Gui)

### Tests

find_package(CppUTest REQUIRED QUIET)
if (CppUTest_FOUND AND NOT TARGET CppUTest::CppUTest)
    add_library(CppUTest::CppUTest INTERFACE IMPORTED)
    set_target_properties(CppUTest::CppUTest PROPERTIES
                          INTERFACE_INCLUDE_DIRECTORIES "${CppUTest_INCLUDE_DIRS}"
                          INTERFACE_LINK_LIBRARIES "${CppUTest_LIBRARIES}")
endif()

set(UNIT_TEST_TARGET tests_unit)
set(UNIT_TEST_SOURCES tests/unit/runner.cpp
                      tests/unit/test_image_io.cpp
                      tests/unit/test_chaos_game.cpp
                      tests/unit/test_cluster_generator.cpp
                      tests/unit/test_kmeans.cpp
                      tests/unit/test_van_eck.cpp)

add_executable(${UNIT_TEST_TARGET} ${UNIT_TEST_SOURCES} ${LIB_SOURCES})
target_compile_features(${UNIT_TEST_TARGET} PRIVATE cxx_std_11)
target_include_directories(${UNIT_TEST_TARGET}
                           PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(${UNIT_TEST_TARGET} PRIVATE basics algorithms synthdata visualization
                                                  CppUTest::CppUTest Qt5::Gui)
