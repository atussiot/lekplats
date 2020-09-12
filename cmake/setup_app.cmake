function (setup_app)
    set(oneValueArgs APP_NAME)
    set(multiValueArgs DEPENDENCIES)

    cmake_parse_arguments(ARG "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(MAIN_TARGET ${ARG_APP_NAME})
    set(APP_SOURCES apps/${ARG_APP_NAME}.cpp)

    add_executable(${MAIN_TARGET} ${APP_SOURCES} ${LIB_SOURCES} ${HEADERS})

    target_include_directories(${MAIN_TARGET}
                               PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
    target_compile_features(${MAIN_TARGET} PRIVATE cxx_std_11)
    target_link_libraries(${MAIN_TARGET} PRIVATE ${ARG_DEPENDENCIES})

endfunction()
