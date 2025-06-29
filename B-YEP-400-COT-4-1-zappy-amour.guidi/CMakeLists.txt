cmake_minimum_required(VERSION 3.16)
project(Zappy)

# Set standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binary)

# Warnings Manage

# if (MSVC)
#   add_compile_options(/W4)
# else()
#   add_compile_options(-Wall -Wextra -Werror)
# endif()

# Add subdirectories

#add_subdirectory(Server)
add_subdirectory(Ai)
#add_subdirectory(Gui)