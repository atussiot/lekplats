cmake_minimum_required(VERSION 3.10)

project(Lekplats VERSION 0.0.1.0
                 DESCRIPTION "Just my personal playground"
                 LANGUAGES CXX)

set(MAIN_TARGET lekplats)

set(APP_SOURCES src/lekplats.cpp)
set(LIB_SOURCES src/cluster_generator.cpp
                src/image_io.cpp
                src/kmeans.cpp
                src/point2D_utils.cpp)

set(HEADERS include/cluster_description.h
            include/cluster_generator.h
            include/image_io.h
            include/kmeans.h
            include/point2D.h
            include/point2D_utils.h)

find_package(Qt5 5.10 REQUIRED QUIET 
                      COMPONENTS Gui)

add_executable(${MAIN_TARGET} ${APP_SOURCES} ${LIB_SOURCES} ${HEADERS})

target_include_directories(${MAIN_TARGET}
                           PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features(${MAIN_TARGET} PRIVATE cxx_std_11)
target_link_libraries(${MAIN_TARGET} PRIVATE Qt5::Gui)


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
                      tests/unit/test_cluster_generator.cpp
                      tests/unit/test_kmeans.cpp)

add_executable(${UNIT_TEST_TARGET} ${UNIT_TEST_SOURCES} ${LIB_SOURCES})
target_compile_features(${UNIT_TEST_TARGET} PRIVATE cxx_std_11)
target_include_directories(${UNIT_TEST_TARGET}
                           PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(${UNIT_TEST_TARGET} PRIVATE CppUTest::CppUTest Qt5::Gui)
