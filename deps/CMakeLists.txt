#
# clog is header only
#
set(DEPS_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/clog/")


#
# CARGO is header only
#
set(DEPS_INCLUDES ${DEPS_INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/cargo/")

#
# lthread
#
add_subdirectory(lthread)
set(DEPS_INCLUDES ${DEPS_INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/lthread/src/")
set(DEPS_LIBRARIES ${DEPS_LIBARRIES} lthread)

#
# return
#
set(DEPS_INCLUDES  ${DEPS_INCLUDES} PARENT_SCOPE)
set(DEPS_LIBRARIES ${DEPS_LIBRARIES} PARENT_SCOPE)

