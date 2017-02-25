#
# clog is header only
#
set(DEPS_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/clog/")


#
# CARGO is header only
#
set(DEPS_INCLUDES ${DEPS_INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/cargo/")

#
# libtask
#
add_subdirectory(libtask)
set(DEPS_INCLUDES ${DEPS_INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/libtask/")
set(DEPS_LIBRARIES ${DEPS_LIBARRIES} ltask)

#
# return
#
set(DEPS_INCLUDES  ${DEPS_INCLUDES} PARENT_SCOPE)
set(DEPS_LIBRARIES ${DEPS_LIBRARIES} PARENT_SCOPE)

