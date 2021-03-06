cmake_minimum_required(VERSION 3.2)

project(wheel-ctn CXX)

if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-command-line-argument")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")

  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fstandalone-debug")
  set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fstandalone-debug")
endif()

if(NOT CMAKE_C_COMPILE_OBJECT)
  if (WIN32)
    set(CMAKE_C_COMPILE_OBJECT ${CMAKE_CXX_COMPILE_OBJECT})
  elseif (APPLE)
    set(CMAKE_C_COMPILE_OBJECT "clang <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
  else()
    set(CMAKE_C_COMPILE_OBJECT "gcc <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
  endif()
endif()

add_subdirectory(src)
add_subdirectory(res)
