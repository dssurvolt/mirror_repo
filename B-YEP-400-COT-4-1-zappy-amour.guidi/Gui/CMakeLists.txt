# gui cmake

file(GLOB_RECURSE GUI_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(zappy_gui ${GUI_SOURCES})

target_include_directories(zappy_gui PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
