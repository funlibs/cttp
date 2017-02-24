cmake_minimum_required (VERSION 2.6)
project (Cttp)

set(CTTP_MAJOR_VERSION 0)
set(CTTP_MINOR_VERSION 1)
set(CTTP_PATCH_VERSION 0)
set(CTTP_VERSION
    ${CTTP_MAJOR_VERSION}.${CTTP_MINOR_VERSION}.${CTTP_PATCH_VERSION})

configure_file(
    ${CMAKE_SOURCE_DIR}/Makefile.in ${CMAKE_SOURCE_DIR}/Makefile)

add_subdirectory(deps/)
include_directories(
    .
    ${DEPS_INCLUDES})

add_executable(cttp cttp.c)

target_link_libraries(cttp ${DEPS_LIBRARIES} pthread)
