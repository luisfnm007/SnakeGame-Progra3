# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appSnake_Game_Progra3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appSnake_Game_Progra3_autogen.dir\\ParseCache.txt"
  "appSnake_Game_Progra3_autogen"
  )
endif()
