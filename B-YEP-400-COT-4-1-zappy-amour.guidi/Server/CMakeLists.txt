
file(GLOB_RECURSE SERVER_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

add_executable(zappy_server ${SERVER_SOURCES})

target_include_directories(zappy_server PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
)