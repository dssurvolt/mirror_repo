
file(GLOB_RECURSE AI_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(zappy_ai ${AI_SOURCES})

target_include_directories(zappy_ai PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
