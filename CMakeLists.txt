cmake_minimum_required (VERSION 2.6)
project (Cttp)

set(CTTP_MAJOR_VERSION 0)
set(CTTP_MINOR_VERSION 1)
set(CTTP_PATCH_VERSION 0)
set(CTTP_VERSION
    ${CTTP_MAJOR_VERSION}.${CTTP_MINOR_VERSION}.${CTTP_PATCH_VERSION})

include_directories(
    deps/cargo/)

add_executable(cttp cttp.c)

# doc
find_package (Doxygen)
if (DOXYGEN_FOUND)

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

  add_custom_target (cttp_doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)

endif (DOXYGEN_FOUND)
