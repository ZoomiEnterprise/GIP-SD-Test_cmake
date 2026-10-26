# file-format: 1.0.0
cmake_minimum_required(VERSION 3.30)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

include(cmake/target.cmake)
include(cmake/${TOOLCHAIN_FILE})

project(GIP-SD-Test C CXX)
add_executable(GIP-SD-Test)
include(cmake/files.cmake)
include(cmake/flags.cmake)
include(cmake/components.cmake)

# Stubs to be able to add compiler flag overrides, e.g. -Os
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
  # Add additional source files here
    "./middleware/Third_Party/FatFs/ff.c"
    "./middleware/Third_Party/FatFs/diskio.c"
    "./middleware/Third_Party/FatFs/fat_sd_spi.c"
    "./middleware/Third_Party/FatFs/syscall.c"
    "./middleware/Third_Party/FatFs/unicode.c"

    "./generated/hal/mx_hal_def.h"

    "SdCard/sd.h"
    "SdCard/sd.c"
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional include directories here
  "middleware/Third_Party/FatFs"
  "SdCard"
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional defined symbols here
)

target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional compiler flags here
)

target_link_options(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker flags here
)

target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker search directories here
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
  # Add additional linker libraries here
)
