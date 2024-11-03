cmake_minimum_required(VERSION 3.12)
project(spacely VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Spacely is a library for dealing with all things 3d.")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(GNUInstallDirs)

# Generate export header
include(GenerateExportHeader)


set(SPACELY_SOURCES
    src/vec3d.cpp
    src/interval.cpp
)

# Create library target
add_library(spacely SHARED ${SPACELY_SOURCES})

generate_export_header(spacely
    BASE_NAME SPACELY
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/spacely_export.h
)

set_target_properties(spacely PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "include/vec3d.h;include/interval.h;${CMAKE_CURRENT_BINARY_DIR}/spacely_export.h"
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_compile_definitions(spacely
    PRIVATE SPACELY_EXPORTS
    PUBLIC $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:SPACELY_STATIC_DEFINE>
)

configure_file(spacely.pc.in spacely.pc @ONLY)

target_include_directories(spacely 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
  include(CTest)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests)
endif()

install(TARGETS spacely
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/spacely.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)