# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appSnake_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appSnake_autogen.dir\\ParseCache.txt"
  "appSnake_autogen"
  )
endif()
