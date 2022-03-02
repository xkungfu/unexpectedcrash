# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\catchfly_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\catchfly_autogen.dir\\ParseCache.txt"
  "catchfly_autogen"
  )
endif()
