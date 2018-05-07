function (setup_library)
    set(oneValueArgs LIB_NAME)
    set(multiValueArgs SOURCES HEADERS DEPENDENCIES)

    cmake_parse_arguments(ARG "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_library(${ARG_LIB_NAME} ${ARG_SOURCES} ${ARG_HEADERS})
    target_compile_features(${ARG_LIB_NAME} PRIVATE cxx_std_11)
    target_include_directories(${ARG_LIB_NAME} 
                               PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
    target_link_libraries(${ARG_LIB_NAME} PRIVATE ${ARG_DEPENDENCIES})

endfunction()
